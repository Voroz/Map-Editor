#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Ui.h"
#include <iostream>

using namespace std;

class MapEditor
{
public:
	MapEditor();
	~MapEditor();
	void run();
};

