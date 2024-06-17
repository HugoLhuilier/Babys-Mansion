#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "RigidBody.h"
#include "StateMachine/BaseState.h"
#include "StateMachine/RoamingState.h"
#include "StateMachine/IdleState.h"
#include "StateMachine/FollowingState.h"


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

	void setRb(RigidBody* nRb) { rb = nRb; }
	void setPlayer(Object* nP) { player = nP; }

private:
	RigidBody* rb;
	Object* player;
	float speed = 50000;

	BaseState* curState;
	RoamingState roamingState;
	IdleState idleState;
	FollowingState followingState;
};