#pragma once

#include "box2d/box2d.h"

/*
* class for when two objects collide and to handle what to do
*/
class ContactListener : public b2ContactListener {
	void BeginContact(b2Contact* contact);
};