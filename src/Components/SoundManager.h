#pragma once

#include "Object.h"

/*
* class to handle spatial sounds 
*/
class AudioListener : public Component {
public:
	using Component::Component;

	/*
	* Function initializing the AudioListener
	*/
	void init() override;

	/*
	* Function updating the AudioListener
	*/
	void update() override;
};