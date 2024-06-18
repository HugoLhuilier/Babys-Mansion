#pragma once

#include "Component.h"

/*
* class created to be used in the unitary tests
*/
class TestComp : public Component {
public:
	using Component::Component;

	/*
	* Function updating TestComp when Game::update() is called
	*/
	void update() override;

	/*
	* Function returning the number of time update() has been called
	*/
	int getNbUpdate() { return nbUpdate; }

private:
	int nbUpdate = 0;
};