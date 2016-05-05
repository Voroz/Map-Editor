#include "Ui.h"


Ui::Ui(sf::RenderWindow& window, Map &map){
	ImGui::SFML::Init(window);
	_map = &map;
	_fallsWhenTouched = false;
	_deadly = false;
	_outlineOnly = false;
	_invertsGravity = false;
	_objectSize[0] = 50;
	_objectSize[1] = 50;
	_worldSize[0] = 8000;
	_worldSize[1] = 800;
	_flags = 0;
	_type = 2;
	_point1[0] = 0.5;
	_point1[1] = 0;
	_point2[0] = 1;
	_point2[1] = 1;
	_point3[0] = 0;
	_point3[1] = 1;
	saveValues();

	_inputSavefile = false;
	_inputLoadfile = false;
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

float* Ui::point1() {
	return _point1;
}
float* Ui::point2() {
	return _point2;
}
float* Ui::point3() {
	return _point3;
}

void Ui::setTooltip(string tooltip) {
	strcpy_s(_tooltip, tooltip.c_str());
}

void Ui::update() {
	ImGui::SFML::Update();
	saveValues();

	ImGui::BeginTooltip();
	ImGui::SetTooltip(_tooltip);
	ImGui::EndTooltip();

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Save")) {
			_inputSavefile = true;
			_inputLoadfile = false;
		}
		if (ImGui::MenuItem("Load")) {
			_inputLoadfile = true;
			_inputSavefile = false;
		}
		if (ImGui::BeginMenu("Recent files")) {
			for (auto &i : _recentFiles) {
				if (ImGui::MenuItem(i.c_str())) {
					loadFile(i);
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();


	if (_inputSavefile == true) {
		ImGui::Begin("Save File", false, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::InputText("file", _filename, 20, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue)) {
			if (!strchr(_filename, '.')) {
				strcat_s(_filename, ".txt");
			}
			saveFile("C:/Users/Jonny/Maps/" + string(_filename));
			_inputSavefile = false;
		}
		ImGui::End();
	}

	if (_inputLoadfile == true) {
		ImGui::Begin("Load File", false, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::InputText("file", _filename, 20, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue)) {
			if (!strchr(_filename, '.')) {
				strcat_s(_filename, ".txt");
			}
			loadFile("C:/Users/Jonny/Maps/" + string(_filename));
			_inputLoadfile = false;
		}
		ImGui::End();
	}

	ImGui::Begin("GUI", false, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::InputInt2("worldSize", _worldSize);
	ImGui::InputInt2("objectSize", _objectSize);
	ImGui::RadioButton("Player", &_type, 2);
	ImGui::RadioButton("Rectangle", &_type, 0);
	ImGui::RadioButton("Triangle", &_type, 1);
	if (_type == 0 || _type == 1) {
		ImGui::Text("\n");
		ImGui::Checkbox("fallsWhenTouched", &_fallsWhenTouched);
		ImGui::Checkbox("deadly", &_deadly);
		ImGui::Checkbox("outlineOnly", &_outlineOnly);
		ImGui::Checkbox("invertsGravity", &_invertsGravity);
	}
	if (_type == 1) {
		ImGui::Text("\nTriangle point offsets:");
		ImGui::SliderFloat2("Point 1", _point1, 0, 1);
		ImGui::SliderFloat2("Point 2", _point2, 0, 1);
		ImGui::SliderFloat2("Point 3", _point3, 0, 1);
	}
	ImGui::End();

	_flags = _fallsWhenTouched * Flag::fallsWhenTouched | _deadly * Flag::deadly | _outlineOnly * Flag::outlineOnly | _invertsGravity * Flag::invertsGravity;
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
	_savedPoint1[0] = _point1[0];
	_savedPoint1[1] = _point1[1];
	_savedPoint2[0] = _point2[0];
	_savedPoint2[1] = _point2[1];
	_savedPoint3[0] = _point3[0];
	_savedPoint3[1] = _point3[1];
}
bool Ui::objectValueChanged() {
	return (_flags != _savedFlags || Vector2<float>(_objectSize[0], _objectSize[1]) != _savedObjectSize || _type != _savedType ||
		_savedPoint1[0] != _point1[0] || _savedPoint1[1] != _point1[1] || _savedPoint2[0] != _point2[0] ||
		_savedPoint2[1] != _point2[1] || _savedPoint3[0] != _point3[0] || _savedPoint3[1] != _point3[1]);
}
void Ui::saveFile(string filepath) {
	ofstream myfile;
	myfile.open(filepath);
	myfile << _worldSize[0] << "," << _worldSize[1] << "\n";
	for (auto &i : _map->gameObjects()) {
		if (i->identify() == 0) {
			myfile << i->identify() << "," << i->flags() << "," << i->pos().x << "," << i->pos().y << "," << i->width() << "," << i->height() << "\n";
		}
		else if (i->identify() == 1) {
			GamePolygonObject *j = static_cast<GamePolygonObject*>(i);
			myfile << i->identify() << "," << j->flags() << "," << j->pos().x << "," << j->pos().y << "," << j->width() << "," << j->height() << "," <<
				j->point1Offset().x << "," << j->point1Offset().y << "," << j->point2Offset().x << "," << j->point2Offset().y << "," <<
				j->point3Offset().x << "," << j->point3Offset().y << "\n";
		}
		if (i->identify() == 2) {
			myfile << i->identify() << "," << i->pos().x << "," << i->pos().y << "," << i->width() << "," << i->height() << "\n";
		}
	}
	//Check if recent filename already exists
	bool exists = false;
	for (auto &i : _recentFiles) {
		if (i == filepath) {
			exists = true;
		}
	}
	if (exists == false) {
		_recentFiles.push_back(filepath);
	}
	myfile.close();
}
void Ui::loadFile(string filepath) {
	ifstream myfile;
	myfile.open(filepath);
	if (myfile.is_open()) {
		for (auto &i : _map->gameObjects()) {
			delete i;
		}
		_map->gameObjects().clear();


		char ch;
		int itemType;
		Vector2<float> pos;
		float width;
		float height;
		Vector2<float> point1Offset;
		Vector2<float> point2Offset;
		Vector2<float> point3Offset;
		int flags;

		myfile >> _worldSize[0] >> ch >> _worldSize[1];
		while (!myfile.eof()) {
			myfile >> itemType >> ch;
			if (itemType == 0) {
				myfile >> flags >> ch >> pos.x >> ch >> pos.y >> ch >> width >> ch >> height;
				_map->gameObjects().push_back(new GameRectObject(pos.x, pos.y, width, height, flags));
			}
			else if (itemType == 1) {
				myfile >> flags >> ch >> pos.x >> ch >> pos.y >> ch >> width >> ch >> height >> ch >>
					point1Offset.x >> ch >> point1Offset.y >> ch >> point2Offset.x >> ch >> point2Offset.y >> ch >> point3Offset.x >> ch >> point3Offset.y;
				_map->gameObjects().push_back(new GamePolygonObject(pos, Vector2<float>(width, height), point1Offset, point2Offset, point3Offset, flags));
			}
			if (itemType == 2) {
				myfile >> pos.x >> ch >> pos.y >> ch >> width >> ch >> height;
				_map->gameObjects().push_front(new Player(pos.x, pos.y, width, height));
			}
		}
		//Check if recent filename already exists
		bool exists = false;
		for (auto &i : _recentFiles) {
			if (i == filepath) {
				exists = true;
			}
		}
		if (exists == false) {
			_recentFiles.push_back(filepath);
		}
		myfile.close();
	}
}