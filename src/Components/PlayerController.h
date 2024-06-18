#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "RigidBody.h"
#include "Game.h"
#include "Components/VisibComp.h"

/*
* class to control the player
*/
class PlayerController : public Component {
public:
	using Component::Component;

	/*
	* Function to set the rigidBody
	*/
	void setRb(RigidBody* nRb);

	/*
	* Function setting the vision system associated with the player
	*/
	void setVisibComp(VisibComp* v) { visibComp = v; }

	/*
	* Function setting the player sprite
	*/
	void setSprite(Sprite* nS) { sprite = nS; }

	/*
	* Function to trigger the lantern bonus
	*/
	void triggerBonus();
	
	/*
	* Function initializing the player controller
	*/
	void init() override;

	/*
	* Function updating the player controller
	*/
	void update() override;

private:
	RigidBody *rb = nullptr;
	float velocity = PLAYER_SPEED;
	b2Vec2 dirVec;
	b2Vec2 appliedForce;
	VisibComp* visibComp;
	Sprite* sprite;

	/*
	* Function updating dirVec (to change the direction to move the player with the forces with box2d)
	*/
	void updateDirVec();
};