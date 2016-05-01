#include "Map.h"



Map::Map(sf::RenderWindow &window, Controls &controls, Ui &ui){
	_window = &window;
	_controls = &controls;
	_ui = &ui;
	_mouseObject = nullptr;
	_worldSize = Vector2<float>(8000, 800);
	_worldRectshape.setSize(sf::Vector2f(_worldSize.x, _worldSize.y));
	_worldRectshape.setPosition(0, 0);
	_worldRectshape.setOutlineThickness(4);
	_worldRectshape.setFillColor(sf::Color::Transparent);
	_worldRectshape.setOutlineColor(sf::Color::Red);
	_view = new MyView(sf::FloatRect(0, 0, 1200, 800), sf::FloatRect(0, 0, _worldSize.x, _worldSize.y));
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
		_view->move(-mouseDiff.x, -mouseDiff.y);
	}
	_savedMousePos = _controls->mouse().pos();

	//Delete mouse item if value changed
	if (_ui->valueChanged()) {
		delete _mouseObject;
		_mouseObject = nullptr;
	}
	//New mouse object if we have none
	if (_mouseObject == nullptr) {
		if (_ui->type() == 0) {
			_mouseObject = new GameRectObject(_controls->mouse().worldPos(), _ui->size(), _ui->flags());
		}
		else if (_ui->type() == 1) {
			_mouseObject = new GamePolygonObject(_controls->mouse().worldPos(), _ui->size(), _ui->flags());
		}
	}
	//Position mouseObject on mouse
	if (_controls->lShift() == true) {
		_mouseObject->setPos(Vector2<float>(align(_controls->mouse().worldPos().x, 10), align(_controls->mouse().worldPos().y, 10)));
	}
	else {
		_mouseObject->setPos(_controls->mouse().worldPos());
	}
	_mouseObject->update();

	vector<GameObject*> mouseOnObjectVector = mouseOnObject();
	//Add new item on mouse click
	if (_controls->mouse().left() == true && mouseOnObjectVector.size() == 0 && _ui->mouseOnWindow() == false && isInWorldrect(_mouseObject)) {
		if (_ui->type() == 0) {
			_gameObjectVector.push_back(new GameRectObject(_mouseObject->pos(), _ui->size(), _ui->flags()));
		}
		else if (_ui->type() == 1) {
			_gameObjectVector.push_back(new GamePolygonObject(_mouseObject->pos(), _ui->size(), _ui->flags()));
		}
	}

	//Delete items on mouse click
	if (_controls->mouse().right() == true && mouseOnObjectVector.size() > 0 && _ui->mouseOnWindow() == false) {
		for (int i = 0; i < _gameObjectVector.size(); i++) {
			for (const auto &j : mouseOnObjectVector) {
				if (_gameObjectVector[i] == j) {
					delete _gameObjectVector[i];
					_gameObjectVector.erase(_gameObjectVector.begin() + i);
				}
			}
		}		
	}
	for (const auto &i : _gameObjectVector) {
		i->update();
	}
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
vector<GameObject*> Map::mouseOnObject() {
	vector<GameObject*> tempVector;
	for (const auto &i : _gameObjectVector) {
		if (i->contains(_controls->mouse().worldPos())) {
			tempVector.push_back(i);
		}
	}
	return tempVector;
}
int Map::align(int value, int size){
	return (value / size)*size + (float)size / 2;
}
bool Map::isInWorldrect(GameObject* gameObj) {
	float aLeft = gameObj->pos().x + gameObj->left();
	float aRight = gameObj->pos().x + gameObj->right();
	float aTop = gameObj->pos().y + gameObj->top();
	float aBottom = gameObj->pos().y + gameObj->bottom();
	return (aLeft >= 0 && aRight <= _worldSize.x &&
		aTop >= 0 && aBottom <= _worldSize.y);
}
vector<GameObject*>& Map::gameObjects() {
	return _gameObjectVector;
}