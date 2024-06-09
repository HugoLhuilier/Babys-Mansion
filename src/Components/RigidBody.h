#pragma once

#include "box2d/box2d.h"
#include "Component.h"


class RigidBody : public Component {
public:

private:
	b2Body body;
};