#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Object;

class CameraController : public Component {
public:
	void update() override;
	void init() override;

private:
	sf::Vector2f upperBound;
	sf::Vector2f lowerBound;
	Object* player;
	sf::RenderWindow* win;
};