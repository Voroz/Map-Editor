#include "Map.h"



Map::Map(sf::RenderWindow &window){
	_window = &window;
	_gameObjectVector.push_back(new GameRectObject(200, 200, 50, 50, Flag::outlineOnly));
}
Map::~Map(){
	for (const auto &i : _gameObjectVector) {
		delete i;
	}
}

void Map::update() {
	for (const auto &i : _gameObjectVector) {
		i->update();
	}
}
void Map::render() {
	for (const auto &i : _gameObjectVector) {
		_window->draw(*i->shape());
	}
}
