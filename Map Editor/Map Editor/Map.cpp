#include "Map.h"



Map::Map(sf::RenderWindow &window, Controls &controls, Ui &ui){
	_window = &window;
	_controls = &controls;
	_ui = &ui;
}
Map::~Map(){
	for (const auto &i : _gameObjectVector) {
		delete i;
	}
}

void Map::update() {
	vector<GameObject*> mouseOnObjectVector = mouseOnObject();
	//Add new item on mouse click
	if (_controls->mouse.leftDown == true && mouseOnObjectVector.size() == 0 && _ui->mouseOnWindow() == false) {
		if (_ui->type() == 0) {
			_gameObjectVector.push_back(new GameRectObject(_controls->mouse.pos, _ui->size(), _ui->flags()));
		}
		else if (_ui->type() == 1) {
			_gameObjectVector.push_back(new GamePolygonObject(_controls->mouse.pos, _ui->size(), _ui->flags()));
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
	for (const auto &i : _gameObjectVector) {
		_window->draw(*i->shape());
	}
}
vector<GameObject*> Map::mouseOnObject() {
	vector<GameObject*> tempVector;
	for (const auto &i : _gameObjectVector) {
		if (i->contains(_controls->mouse.pos)) {
			tempVector.push_back(i);
		}
	}
	return tempVector;
}
