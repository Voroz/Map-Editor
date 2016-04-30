#include "MapEditor.h"


MapEditor::MapEditor(){
}
MapEditor::~MapEditor(){
}

void MapEditor::run() {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Map Editor");
	window.setFramerateLimit(200);
	Ui ui(window);
	Controls controls(window);
	Map map(window, controls, ui);

	while (window.isOpen()) {
		sf::Event event;
		controls.mouse().setMouseWheel(0);
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseMoved) {
				controls.mouse().setPos(Vector2<float>(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					controls.mouse().setLeft(true);
				}
				if (event.key.code == sf::Mouse::Right) {
					controls.mouse().setRight(true);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.key.code == sf::Mouse::Left) {
					controls.mouse().setLeft(false);
				}
				if (event.key.code == sf::Mouse::Right) {
					controls.mouse().setRight(false);
				}
			}
			if (event.type == sf::Event::MouseWheelMoved) {
				controls.mouse().setMouseWheel(event.mouseWheel.delta);
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::LShift) {
					controls.setLShift(true);
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::LShift) {
					controls.setLShift(false);
				}
			}
		}

		ui.update();
		map.update();

		window.clear();
		map.render();
		ui.render();
		window.display();
	}
}
