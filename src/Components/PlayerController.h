#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "RigidBody.h"


class PlayerController : public Component {
public:

private:
	RigidBody *rb;
};