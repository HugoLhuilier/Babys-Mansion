#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Object;

/*
* class to control the camera
*/
class CameraController : public Component {
public:
	using Component::Component;

	/*
	* Function updating the camera controller
	*/
	void update() override;

	/*
	* Function initializing the camera controller
	*/
	void init() override;

	/*
	* Function setting the player (on whom the camera will focus)
	*/
	void setPlayer(Object*);

	/*
	* Function setting the bounds
	*/
	void setBounds(sf::Vector2f lower, sf::Vector2f upper);

private:
	sf::Vector2f upperBound;
	sf::Vector2f lowerBound;
	Object* player;
	sf::RenderWindow* win;
};