#pragma once

#include "box2d/box2d.h"

class ContactListener : public b2ContactListener {
	void BeginContact(b2Contact* contact);
};