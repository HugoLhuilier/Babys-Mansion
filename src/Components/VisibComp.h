#pragma once

#include "Component.h"
#include "Object.h"
#include "Components/Sprite.h"


/*
* class to handle the vision in a circle for the player
*/
class VisibComp : public Component {
public:
	using Component::Component;

	/*
	* Function udating the visibility when game::update() is called
	*/
	void update() override;

	/*
	* Function to extend the light when you get a lantern bonus
	*/
	void extendLight();

	/*
	* Function setting the player
	*/
	void setPlayer(Object* nP) { player = nP; }

	/*
	* Function setting the sprite
	*/
	void setSprite(Sprite* nSprite) { sprite = nSprite; }

private:
	Object* player;
	Sprite* sprite;

	float bonusTime = 5;
	float extendTime = 1;
	float lightSizeFact = 3;

	sf::Clock clock;

	/*
	* Function setting the size of the sprite 
	*/
	void setSpriteSize();
};