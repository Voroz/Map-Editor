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
	Map map(window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
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
