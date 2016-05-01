#include "Ui.h"


Ui::Ui(sf::RenderWindow& window){
	ImGui::SFML::Init(window);
	_fallsWhenTouched = false;
	_deadly = false;
	_outlineOnly = false;
	_objectSize[0] = 50;
	_objectSize[1] = 50;
	_worldSize[0] = 8000;
	_worldSize[1] = 800;
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

Vector2<float>& Ui::objectSize() {
	return Vector2<float>(_objectSize[0], _objectSize[1]);
}

int* Ui::worldSize() {
	return _worldSize;
}
void Ui::setTooltip(string tooltip) {
	strcpy_s(_tooltip, tooltip.c_str());
}

void Ui::update(vector<GameObject*> &gameObjectVector) {
	ImGui::SFML::Update();
	saveValues();

	ImGui::BeginTooltip();
	ImGui::SetTooltip(_tooltip);
	ImGui::EndTooltip();

	ImGui::Begin("Filehandler");
	if (ImGui::SmallButton("save")) {
		ofstream myfile;
		if (!strchr(_filename, '.')) {
			strcat_s(_filename, ".txt");
		}
		myfile.open(_filename);
		myfile << _worldSize[0] << "," << _worldSize[1] << "\n";
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


			char ch;
			int itemType;
			Vector2<float> pos;
			float width;
			float height;
			int flags;

			myfile >> _worldSize[0] >> ch >> _worldSize[1];
			while (!myfile.eof()) {
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
	ImGui::InputInt2("worldSize", _worldSize);
	ImGui::InputInt2("objectSize", _objectSize);
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
	_savedObjectSize = objectSize();
	_savedType = type();
}
bool Ui::objectValueChanged() {
	return (_flags != _savedFlags || Vector2<float>(_objectSize[0], _objectSize[1]) != _savedObjectSize || _type != _savedType);
}