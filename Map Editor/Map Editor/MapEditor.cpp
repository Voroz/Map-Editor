#include "MapEditor.h"
#include "Map.h"


MapEditor::MapEditor(){
}
MapEditor::~MapEditor(){
}

void MapEditor::run() {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Map Editor");
	window.setFramerateLimit(60);
	Ui ui(window);
	Controls controls;
	Map map(window, controls, ui);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseMoved) {
				controls.mouse.pos = Vector2<float>(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					controls.mouse.leftDown = true;
				}
				if (event.key.code == sf::Mouse::Right) {
					controls.mouse.rightDown = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.key.code == sf::Mouse::Left) {
					controls.mouse.leftDown = false;
				}
				if (event.key.code == sf::Mouse::Right) {
					controls.mouse.rightDown = false;
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
