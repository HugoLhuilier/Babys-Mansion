#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "RigidBody.h"


class PlayerController : public Component {
public:
	using Component::Component;

	void setRb(RigidBody* nRb);
	
	void init() override;
	void update() override;

private:
	RigidBody *rb = nullptr;
	float velocity = 1000000;
	b2Vec2 dirVec;
	b2Vec2 appliedForce;

	void updateDirVec();
};