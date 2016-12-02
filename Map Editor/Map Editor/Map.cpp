#include "Map.h"



Map::Map(sf::RenderWindow &window, Controls &controls){
	_window = &window;
	_controls = &controls;
	_mouseObject = nullptr;
	_worldRectshape.setPosition(0, 0);
	_worldRectshape.setOutlineThickness(4);
	_worldRectshape.setFillColor(sf::Color::Transparent);
	_worldRectshape.setOutlineColor(sf::Color::Red);
}
Map::~Map(){
	for (const auto &i : _gameObjectVector) {
		delete i;
	}
	delete _mouseObject;
}

void Map::setUi(Ui &ui) {
	_ui = &ui;
	_worldSize.x = &_ui->worldSize()[0];
	_worldSize.y = &_ui->worldSize()[1];
	_worldRectshape.setSize(sf::Vector2f(*_worldSize.x, *_worldSize.y));
	_view = new MyView(sf::FloatRect(0, 0, 1200, 800), sf::FloatRect(0, 0, *_worldSize.x, *_worldSize.y));
}

void Map::saveFile(string filepath) {
	ofstream myfile;
	myfile.open(filepath);
	myfile << _ui->worldSize()[0] << "," << _ui->worldSize()[1] << "\n";
	for (auto &i : _gameObjectVector) {
		myfile << i->identify() << "," << i->pos().x << "," << i->pos().y << "," << i->width() << "," << i->height() << ","
			<< i->mass() << "," << i->bouncyness() << "," << i->gravityMultiplier().x << "," << i->gravityMultiplier().y << ",";
		if (i->identify() == 0) {
			myfile << i->physicsType() << "," << i->flags() << "\n";
		}
		else if (i->identify() == 1) {
			GamePolygonObject *j = static_cast<GamePolygonObject*>(i);
			myfile << i->physicsType() << "," << j->flags() << "," << j->point1Offset().x << "," << j->point1Offset().y << ","
				<< j->point2Offset().x << "," << j->point2Offset().y << "," << j->point3Offset().x << "," << j->point3Offset().y << "\n";
		}
		if (i->identify() == 2) {
			myfile << "\n";
		}
	}
	/*//Check if recent filename already exists
	bool exists = false;
	for (auto &i : _recentFiles) {
		if (i == filepath) {
			exists = true;
		}
	}
	if (exists == false) {
		_recentFiles.push_back(filepath);
	}*/
	myfile.close();
}

void Map::loadFile(string filepath) {
	ifstream myfile;
	myfile.open(filepath);
	if (myfile.is_open()) {
		for (auto &i : _gameObjectVector) {
			delete i;
		}
		_gameObjectVector.clear();


		char ch;
		int itemType;
		Vector2<float> pos;
		float width;
		float height;
		Vector2<float> point1Offset;
		Vector2<float> point2Offset;
		Vector2<float> point3Offset;
		int flags;
		int physicsType;
		float mass;
		float bouncyness;
		Vector2<float> gravityMultiplier;

		myfile >> _ui->worldSize()[0] >> ch >> _ui->worldSize()[1];
		while (!myfile.eof()) {
			myfile >> itemType >> ch >> pos.x >> ch >> pos.y >> ch >> width >> ch >> height >> ch >> mass >> ch >> bouncyness >> ch
				>> gravityMultiplier.x >> ch >> gravityMultiplier.y >> ch;

			if (itemType == 0) {
				myfile >> physicsType >> ch >> flags;
				_gameObjectVector.push_back(new GameRectObject(physicsType, pos.x, pos.y, width, height, mass, bouncyness, gravityMultiplier, flags));
			}

			else if (itemType == 1) {
				myfile >> physicsType >> ch >> flags >> ch >>
					point1Offset.x >> ch >> point1Offset.y >> ch >> point2Offset.x >> ch >> point2Offset.y >> ch >> point3Offset.x >> ch >> point3Offset.y;
				_gameObjectVector.push_back(new GamePolygonObject(physicsType, pos, Vector2<float>(width, height), mass, bouncyness, gravityMultiplier, point1Offset, point2Offset, point3Offset, flags));
			}

			if (itemType == 2) {
				_gameObjectVector.push_front(new Player(pos.x, pos.y, width, height, mass, bouncyness, gravityMultiplier));
			}
		}
		/*//Check if recent filename already exists
		bool exists = false;
		for (auto &i : _recentFiles) {
			if (i == filepath) {
				exists = true;
			}
		}
		if (exists == false) {
			_recentFiles.push_back(filepath);
		}*/
		myfile.close();
	}
}

void Map::update() {
	//Delete mouse item if value changed
	if (_ui->objectValueChanged()) {
		delete _mouseObject;
		_mouseObject = nullptr;
	}
	//New mouse object if we have none
	if (_mouseObject == nullptr) {
		if (_ui->objectType() == 0) {
			_mouseObject = new GameRectObject(_ui->physicsType(), _controls->mouse().worldPos(), _ui->objectSize(), _ui->mass(), _ui->bouncyness(), _ui->gravityMultiplier(), _ui->flags());
		}
		else if (_ui->objectType() == 1) {
			_mouseObject = new GamePolygonObject(_ui->physicsType(), _controls->mouse().worldPos(), _ui->objectSize(), _ui->mass(), _ui->bouncyness(), _ui->gravityMultiplier(), Vector2<float>(_ui->point1()[0], _ui->point1()[1]),
				Vector2<float>(_ui->point2()[0], _ui->point2()[1]), Vector2<float>(_ui->point3()[0], _ui->point3()[1]), _ui->flags());
		}
		else if (_ui->objectType() == 2) {
			_mouseObject = new Player(_controls->mouse().worldPos(), _ui->objectSize(), _ui->mass(), _ui->bouncyness(), _ui->gravityMultiplier());
		}
	}
	//Position mouseObject on mouse
	if (_controls->lShift() == true) {
		_mouseObject->setPos(Vector2<float>(align(_controls->mouse().worldPos().x, 5), align(_controls->mouse().worldPos().y, 5)));
	}
	else {
		_mouseObject->setPos((int)_controls->mouse().worldPos().x, (int)_controls->mouse().worldPos().y);
	}

	if (_ui->mouseOnWindow() == false) {
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

		deque<GameObject*> mouseOnObjectVector = mouseOnObject();
		//Add new item on mouse click
		if (_controls->mouse().left() == true && mouseOnObjectVector.size() == 0 && isInWorldrect(_mouseObject)) {
			if (_ui->objectType() == 0) {
				_gameObjectVector.push_back(new GameRectObject(_ui->physicsType(), _mouseObject->pos(), _ui->objectSize(), _ui->mass(), _ui->bouncyness(), _ui->gravityMultiplier(), _ui->flags()));
			}
			else if (_ui->objectType() == 1) {
				_gameObjectVector.push_back(new GamePolygonObject(_ui->physicsType(), _mouseObject->pos(), _ui->objectSize(), _ui->mass(), _ui->bouncyness(), _ui->gravityMultiplier(), Vector2<float>(_ui->point1()[0], _ui->point1()[1]),
					Vector2<float>(_ui->point2()[0], _ui->point2()[1]), Vector2<float>(_ui->point3()[0], _ui->point3()[1]), _ui->flags()));
			}
			else if (_ui->objectType() == 2 && !objectTypeExists(2)) {
				_gameObjectVector.push_front(new Player(_mouseObject->pos(), _ui->objectSize(), _ui->mass(), _ui->bouncyness(), _ui->gravityMultiplier()));
			}
		}

		//Delete items on mouse click
		if (_controls->mouse().right() == true && mouseOnObjectVector.size() > 0) {
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
	}

	for (const auto &i : _gameObjectVector) {
		i->update();
	}
	_mouseObject->update();

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

	_savedMousePos = _controls->mouse().pos();
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