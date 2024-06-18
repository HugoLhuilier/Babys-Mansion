#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "RigidBody.h"
#include "StateMachine/BaseState.h"
#include "StateMachine/RoamingState.h"
#include "StateMachine/IdleState.h"
#include "StateMachine/FollowingState.h"
#include "Game.h"
#include "Components/Sprite.h"


enum class StateTag {
	Idle,
	Roaming,
	Following
};

class BabyController : public Component {
public:
	using Component::Component;

	void init() override;
	void update() override;

	void switchState(StateTag newState);

	float getSpeed() const { return speed; }
	RigidBody* getRb() const { return rb; }
	Object* getPlayer() const { return player; }
	Sprite* getSprite() const { return sprite; }

	void setRb(RigidBody* nRb) { rb = nRb; }
	void setPlayer(Object* nP) { player = nP; }
	void setSprite(Sprite* nS) { sprite = nS; }

private:
	RigidBody* rb;
	Object* player;
	float speed = PLAYER_SPEED * 0.7;

	BaseState* curState;
	RoamingState roamingState;
	IdleState idleState;
	FollowingState followingState;
	Sprite* sprite;
};