#include "Ui.h"


Ui::Ui(sf::RenderWindow& window){
	ImGui::SFML::Init(window);
	_fallsWhenTouched = false;
	_deadly = false;
	_outlineOnly = false;
	_size[0] = 50;
	_size[1] = 50;
	_flags = 0;
	_type = 0;
	saveValues();
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

Vector2<float>& Ui::size() {
	return Vector2<float>(_size[0], _size[1]);
}

void Ui::update() {
	ImGui::SFML::Update();
	saveValues();

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
bool Ui::mouseOnWindow() {
	return ImGui::IsMouseHoveringAnyWindow();
}
void Ui::saveValues() {
	_savedFlags = flags();
	_savedSize = size();
	_savedType = type();
}
bool Ui::valueChanged() {
	return (_flags != _savedFlags || Vector2<float>(_size[0], _size[1]) != _savedSize || _type != _savedType);
}