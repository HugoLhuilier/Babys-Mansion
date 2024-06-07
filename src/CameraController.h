#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Object;

class CameraController {
public:

private:
	sf::RenderWindow win;
	Object& player;
};