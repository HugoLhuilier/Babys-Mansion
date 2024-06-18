#pragma once

#include "Component.h"
#include "Object.h"


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
	* Function setting the player on which to focus the circle of vision 
	*/
	void setPlayer(Object* nP) { player = nP; }

private:
	Object* player;
};