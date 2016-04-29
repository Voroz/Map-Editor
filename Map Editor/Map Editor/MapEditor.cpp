#include "MapEditor.h"


MapEditor::MapEditor(){
}
MapEditor::~MapEditor(){
}

void MapEditor::run() {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Map Editor");
	window.setFramerateLimit(60);
	Ui ui(window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ui.update();

		window.clear();
		ui.render();
		window.display();
	}
}
