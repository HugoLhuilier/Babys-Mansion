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

	void extendLight();

	void setPlayer(Object* nP) { player = nP; }
	void setSprite(Sprite* nSprite) { sprite = nSprite; }

private:
	Object* player;
	Sprite* sprite;

	float bonusTime = 5;
	float extendTime = 1;
	float lightSizeFact = 3;

	sf::Clock clock;

	void setSpriteSize();
};