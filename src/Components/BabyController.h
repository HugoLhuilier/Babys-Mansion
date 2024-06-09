#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "RigidBody.h"
//#include "Object.h"


class BabyController : public Component {
public:
private:
	RigidBody* rb;
	Object* player;
};