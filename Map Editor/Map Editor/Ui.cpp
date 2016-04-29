#include "Ui.h"


Ui::Ui(sf::RenderWindow& window){
	ImGui::SFML::Init(window);
	_fallsWhenTouched = false;
	_deadly = false;
	_outlineOnly = false;
	_size[0] = 0;
	_size[1] = 0;
	_flags = 0;
	_type = 0;
}
Ui::~Ui(){
	ImGui::SFML::Shutdown();
}

int& Ui::type() {
	return _type;
}

int& Ui::flags() {
	return _flags;
}

Vector2<int>& Ui::size() {
	return Vector2<int>(_size[0], _size[1]);
}

void Ui::update() {
	ImGui::SFML::Update();

	ImGui::Begin("GUI");
	ImGui::InputInt2("Size", _size);
	ImGui::Checkbox("fallsWhenTouched", &_fallsWhenTouched);
	ImGui::Checkbox("deadly", &_deadly);
	ImGui::Checkbox("outlineOnly", &_outlineOnly);
	ImGui::RadioButton("Rectangle", &_type, 0);
	ImGui::RadioButton("Triangle", &_type, 1);
	ImGui::End();

	_flags = _fallsWhenTouched * Flag::fallsWhenTouched | _deadly * Flag::deadly | _outlineOnly * Flag::outlineOnly;
}
void Ui::render() {
	ImGui::Render();
}
