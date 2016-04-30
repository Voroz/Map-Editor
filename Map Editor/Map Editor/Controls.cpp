#include "Controls.h"

Controls::Controls(sf::RenderWindow &window) : _mouse(window) {
	_lShift = false;
}
Controls::~Controls() {

}

Mouse& Controls::mouse() {
	return _mouse;
}
bool Controls::lShift() {
	return _lShift;
}
void Controls::setLShift(bool down) {
	_lShift = down;
}