#include "Map.h"



Map::Map(sf::RenderWindow &window, Controls &controls, Ui &ui){
	_window = &window;
	_controls = &controls;
	_ui = &ui;
	_mouseObject = nullptr;
	_worldSize.x = &_ui->worldSize()[0];
	_worldSize.y = &_ui->worldSize()[1];
	_worldRectshape.setSize(sf::Vector2f(*_worldSize.x, *_worldSize.y));
	_worldRectshape.setPosition(0, 0);
	_worldRectshape.setOutlineThickness(4);
	_worldRectshape.setFillColor(sf::Color::Transparent);
	_worldRectshape.setOutlineColor(sf::Color::Red);
	_view = new MyView(sf::FloatRect(0, 0, 1200, 800), sf::FloatRect(0, 0, *_worldSize.x, *_worldSize.y));
}
Map::~Map(){
	for (const auto &i : _gameObjectVector) {
		delete i;
	}
	delete _mouseObject;
}

void Map::update() {
	//Zoom view on mouse scroll
	if (_controls->mouse().wheel() > 0) {
		_view->zoom(abs(_controls->mouse().wheel()) / 1.2f);
	}
	else if (_controls->mouse().wheel() < 0) {
		_view->zoom(abs(_controls->mouse().wheel()) * 1.2f);
	}

	//Move view on mouse scroll click
	if (_controls->mouse().wheelClick() == true && _savedMousePos != _controls->mouse().pos()) {
		Vector2<float> mouseDiff = _controls->mouse().pos() - _savedMousePos;
		_view->move(-mouseDiff.x * _view->currentZoom(), -mouseDiff.y * _view->currentZoom());
	}
	_savedMousePos = _controls->mouse().pos();

	//Delete mouse item if value changed
	if (_ui->objectValueChanged()) {
		delete _mouseObject;
		_mouseObject = nullptr;
	}
	//New mouse object if we have none
	if (_mouseObject == nullptr) {
		if (_ui->type() == 0) {
			_mouseObject = new GameRectObject(_controls->mouse().worldPos(), _ui->objectSize(), _ui->flags());
		}
		else if (_ui->type() == 1) {
			_mouseObject = new GamePolygonObject(_controls->mouse().worldPos(), _ui->objectSize(), Vector2<float>(_ui->point1()[0], _ui->point1()[1]),
				Vector2<float>(_ui->point2()[0], _ui->point2()[1]), Vector2<float>(_ui->point3()[0], _ui->point3()[1]), _ui->flags());
		}
		else if (_ui->type() == 2) {
			_mouseObject = new Player(_controls->mouse().worldPos(), _ui->objectSize());
		}
	}
	//Position mouseObject on mouse
	if (_controls->lShift() == true) {
		_mouseObject->setPos(Vector2<float>(align(_controls->mouse().worldPos().x, 5), align(_controls->mouse().worldPos().y, 5)));
	}
	else {
		_mouseObject->setPos((int)_controls->mouse().worldPos().x, (int)_controls->mouse().worldPos().y);
	}
	_mouseObject->update();

	deque<GameObject*> mouseOnObjectVector = mouseOnObject();
	//Add new item on mouse click
	if (_controls->mouse().left() == true && mouseOnObjectVector.size() == 0 && _ui->mouseOnWindow() == false && isInWorldrect(_mouseObject)) {
		if (_ui->type() == 0) {
			_gameObjectVector.push_back(new GameRectObject(_mouseObject->pos(), _ui->objectSize(), _ui->flags()));
		}
		else if (_ui->type() == 1) {
			_gameObjectVector.push_back(new GamePolygonObject(_mouseObject->pos(), _ui->objectSize(), Vector2<float>(_ui->point1()[0], _ui->point1()[1]),
				Vector2<float>(_ui->point2()[0], _ui->point2()[1]), Vector2<float>(_ui->point3()[0], _ui->point3()[1]), _ui->flags()));
		}
		else if (_ui->type() == 2 && !objectTypeExists(2)) {
			_gameObjectVector.push_front(new Player(_mouseObject->pos(), _ui->objectSize()));
		}
	}

	//Delete items on mouse click
	if (_controls->mouse().right() == true && mouseOnObjectVector.size() > 0 && _ui->mouseOnWindow() == false) {
		for (int i = 0; i < _gameObjectVector.size(); i++) {
			for (const auto &j : mouseOnObjectVector) {
				if (_gameObjectVector[i] == j) {
					delete _gameObjectVector[i];
					_gameObjectVector[i] = nullptr;
					_gameObjectVector.erase(_gameObjectVector.begin() + i);
				}
			}
		}		
	}
	for (const auto &i : _gameObjectVector) {
		i->update();
	}

	//Match world rect to objects if world rect became too small.
	for (auto &i : _gameObjectVector) {
		if (isInWorldXrect(i) == false) {
			matchWorldXToObjects();
		}
		if (isInWorldYrect(i) == false) {
			matchWorldYToObjects();
		}
	}

	//Set mouseObject coordinate tooltip
	_ui->setTooltip(to_string((int)_mouseObject->pos().x) + ", " + to_string((int)_mouseObject->pos().y));

	//Sync world rect.
	sync();
}
void Map::render() {
	_window->setView(*_view);
	for (const auto &i : _gameObjectVector) {
		_window->draw(*i->shape());
	}
	if (_ui->mouseOnWindow() == false) {
		_window->draw(*_mouseObject->shape());
	}
	_window->draw(_worldRectshape);
}
deque<GameObject*> Map::mouseOnObject() {
	deque<GameObject*> tempVector;
	for (const auto &i : _gameObjectVector) {
		if (i->contains(_controls->mouse().worldPos())) {
			tempVector.push_back(i);
		}
	}
	return tempVector;
}
void Map::sync() {
	_worldRectshape.setSize(sf::Vector2f(*_worldSize.x, *_worldSize.y));
}
int Map::align(int value, int size){
	return (value / size)*size;
}
bool Map::isInWorldrect(GameObject* gameObj) {
	float aLeft = gameObj->pos().x + gameObj->left();
	float aRight = gameObj->pos().x + gameObj->right();
	float aTop = gameObj->pos().y + gameObj->top();
	float aBottom = gameObj->pos().y + gameObj->bottom();
	return (aLeft >= 0 && aRight <= *_worldSize.x &&
		aTop >= 0 && aBottom <= *_worldSize.y);
}
bool Map::isInWorldXrect(GameObject* gameObj) {
	float aLeft = gameObj->pos().x + gameObj->left();
	float aRight = gameObj->pos().x + gameObj->right();
	return (aLeft >= 0 && aRight <= *_worldSize.x);
}
bool Map::isInWorldYrect(GameObject* gameObj) {
	float aTop = gameObj->pos().y + gameObj->top();
	float aBottom = gameObj->pos().y + gameObj->bottom();
	return (aTop >= 0 && aBottom <= *_worldSize.y);
}
void Map::matchWorldXToObjects() {
	float max = 0;
	for (auto &i : _gameObjectVector) {
		float x = i->pos().x + i->right();
		if (x > max) {
			max = x;
		}
	}
	*_worldSize.x = max;
}
void Map::matchWorldYToObjects() {
	float max = 0;
	for (auto &i : _gameObjectVector) {
		float y = i->pos().y + i->bottom();
		if (y > max) {
			max = y;
		}
	}
	*_worldSize.y = max;
}
deque<GameObject*>& Map::gameObjects() {
	return _gameObjectVector;
}
bool Map::objectTypeExists(int type) {
	for (auto &i : _gameObjectVector) {
		if (i->identify() == type) {
			return true;
		}
	}
	return false;
}