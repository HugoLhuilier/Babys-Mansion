#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "RigidBody.h"
#include "Game.h"
#include "Components/VisibComp.h"


class PlayerController : public Component {
public:
	using Component::Component;

	void setRb(RigidBody* nRb);
	void setVisibComp(VisibComp* v) { visibComp = v; }
	void setSprite(Sprite* nS) { sprite = nS; }
	void triggerBonus();
	
	void init() override;
	void update() override;

private:
	RigidBody *rb = nullptr;
	float velocity = PLAYER_SPEED;
	b2Vec2 dirVec;
	b2Vec2 appliedForce;
	VisibComp* visibComp;
	Sprite* sprite;

	void updateDirVec();
};