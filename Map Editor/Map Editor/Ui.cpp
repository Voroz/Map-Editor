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

	strcpy_s(_filename, "");
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

void Ui::update(vector<GameObject*> &gameObjectVector) {
	ImGui::SFML::Update();
	saveValues();

	ImGui::Begin("Filehandler");
	if (ImGui::SmallButton("save")) {
		ofstream myfile;
		if (!strchr(_filename, '.')) {
			strcat_s(_filename, ".txt");
		}
		myfile.open(_filename);
		for (auto &i : gameObjectVector) {
			myfile << i->identify() << "," << i->pos().x << "," << i->pos().y << "," << i->width() << "," << i->height() << "," << i->flags() << "\n";
		}
		myfile.close();
	}
	if (ImGui::SmallButton("load")) {
		ifstream myfile;
		if (!strchr(_filename, '.')) {
			strcat_s(_filename, ".txt");
		}
		myfile.open(_filename);
		if (myfile.is_open()) {
			for (auto &i : gameObjectVector) {
				delete i;
			}
			gameObjectVector.clear();

			int itemType;
			Vector2<float> pos;
			float width;
			float height;
			int flags;
			while (!myfile.eof()) {
				char ch;
				myfile >> itemType >> ch >> pos.x >> ch >> pos.y >> ch >> width >> ch >> height >> ch >> flags;
				if (itemType == 0) {
					gameObjectVector.push_back(new GameRectObject(pos.x, pos.y, width, height, flags));
				}
				else if (itemType == 1) {
					gameObjectVector.push_back(new GamePolygonObject(pos, Vector2<float>(width, height), flags));
				}
			}
			myfile.close();
		}
	}
	ImGui::InputText("File", _filename, 20);
	ImGui::End();
	
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