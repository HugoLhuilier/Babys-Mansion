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

/*
* differet State tag to know in which state is the baby 
*/
enum class StateTag {
	Idle,
	Roaming,
	Following
};

/*
* class to control the baby
*/
class BabyController : public Component {
public:
	using Component::Component;

	/*
	* Function initializing the baby controller
	*/
	void init() override;

	/*
	* Function updating the baby controller
	*/
	void update() override;

	/*
	* Function to switch the state of the baby into the state newState
	*/
	void switchState(StateTag newState);

	/*
	* Function returning a pointer to the current state
	*/
	BaseState* getState() { return curState; }

	/*
	* Function returning the speed of the baby
	*/
	float getSpeed() const { return speed; }

	/*
	* Function returning a pointer to the rigid body of the baby
	*/
	RigidBody* getRb() const { return rb; }

	/*
	* Function returning a pointer of the player followed 
	*/
	Object* getPlayer() const { return player; }
	Sprite* getSprite() const { return sprite; }

	/*
	* Function setting the rigid body of the baby
	*/
	void setRb(RigidBody* nRb) { rb = nRb; }

	/*
	* Function setting the player to chase
	*/
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