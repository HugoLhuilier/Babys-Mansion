#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Object;

class CameraController : public Component {
public:
	using Component::Component;

	void update() override;
	void init() override;

	void setPlayer(Object*);
	void setBounds(sf::Vector2f lower, sf::Vector2f upper);

private:
	sf::Vector2f upperBound;
	sf::Vector2f lowerBound;
	Object* player;
	sf::RenderWindow* win;
};