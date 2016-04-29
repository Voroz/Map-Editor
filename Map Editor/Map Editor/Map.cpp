#include "Map.h"



Map::Map(sf::RenderWindow &window){
	_window = &window;
}
Map::~Map(){
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
