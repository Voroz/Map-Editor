#include "Map.h"



Map::Map(sf::RenderWindow &window, Controls &controls, Ui &ui){
	_window = &window;
	_controls = &controls;
	_ui = &ui;
	_mouseObject = nullptr;
	_worldSize = Vector2<float>(8000, 800);
	_view = new MyView(sf::FloatRect(0, 0, 1200, 800), sf::FloatRect(0, 0, _worldSize.x, _worldSize.y));
}
Map::~Map(){
	for (const auto &i : _gameObjectVector) {
		delete i;
	}
	delete _mouseObject;
}

void Map::update() {
	//Delete mouse item if value changed
	if (_ui->valueChanged()) {
		delete _mouseObject;
		_mouseObject = nullptr;
	}
	//New mouse object if we have none
	if (_mouseObject == nullptr) {
		if (_ui->type() == 0) {
			_mouseObject = new GameRectObject(_controls->mouse.pos, _ui->size(), _ui->flags());
		}
		else if (_ui->type() == 1) {
			_mouseObject = new GamePolygonObject(_controls->mouse.pos, _ui->size(), _ui->flags());
		}
	}
	//Position mouseObject on mouse
	if (_controls->lShift == true) {
		_mouseObject->setPos(Vector2<float>(align(_controls->mouse.pos.x + _view->getCenter().x - _view->getSize().x / 2, 10), align(_controls->mouse.pos.y + _view->getCenter().y - _view->getSize().y / 2, 10)));
	}
	else {
		_mouseObject->setPos(Vector2<float>(_window->mapPixelToCoords(sf::Vector2i(_controls->mouse.pos.x, _controls->mouse.pos.y)).x, _window->mapPixelToCoords(sf::Vector2i(_controls->mouse.pos.x, _controls->mouse.pos.y)).y));
	}
	_mouseObject->update();

	vector<GameObject*> mouseOnObjectVector = mouseOnObject();
	//Add new item on mouse click
	if (_controls->mouse.leftDown == true && mouseOnObjectVector.size() == 0 && _ui->mouseOnWindow() == false) {
		if (_ui->type() == 0) {
			_gameObjectVector.push_back(new GameRectObject(_mouseObject->pos(), _ui->size(), _ui->flags()));
		}
		else if (_ui->type() == 1) {
			_gameObjectVector.push_back(new GamePolygonObject(_mouseObject->pos(), _ui->size(), _ui->flags()));
		}
	}

	//Delete items on mouse click
	if (_controls->mouse.rightDown == true && mouseOnObjectVector.size() > 0 && _ui->mouseOnWindow() == false) {
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
	_window->draw(*_mouseObject->shape());
}
vector<GameObject*> Map::mouseOnObject() {
	vector<GameObject*> tempVector;
	for (const auto &i : _gameObjectVector) {
		if (i->contains(Vector2<float>(_window->mapPixelToCoords(sf::Vector2i(_controls->mouse.pos.x, _controls->mouse.pos.y)).x, _window->mapPixelToCoords(sf::Vector2i(_controls->mouse.pos.x, _controls->mouse.pos.y)).y))) {
			tempVector.push_back(i);
		}
	}
	return tempVector;
}
int Map::align(int value, int size){
	return (value / size)*size + (float)size / 2;
}