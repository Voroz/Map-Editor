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
	//Add new item on mouse click
	if (_controls->mouse.leftDown == true && mouseOnObject() == false && _ui->mouseOnWindow() == false) {
		if (_ui->type() == 0) {
			_gameObjectVector.push_back(new GameRectObject(_controls->mouse.pos, _ui->size(), _ui->flags()));
		}
		else if (_ui->type() == 1) {
			_gameObjectVector.push_back(new GamePolygonObject(_controls->mouse.pos, _ui->size(), _ui->flags()));
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
bool Map::mouseOnObject() {
	for (const auto &i : _gameObjectVector) {
		if (i->contains(_controls->mouse.pos)) {
			return true;
		}
	}
	return false;
}
