#include "PlayerController.h"
#include "Object.h"
#include <iostream>

using namespace std;

void PlayerController::setRb(RigidBody* nRb)
{
	rb = nRb;
}

void PlayerController::init()
{
	getObject()->getGame()->setPlayerCtrl(this);
}

void PlayerController::update()
{
	if (rb) {
		updateDirVec();
		if (appliedForce.LengthSquared() == 0) {
			rb->resetSpeed();
		}
		else 
			rb->addForce(appliedForce);
	}
}

void PlayerController::updateDirVec()
{
	if (rb) {
		dirVec.SetZero();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			dirVec += b2Vec2(1, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			dirVec += b2Vec2(0, 1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			dirVec += b2Vec2(-1, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			dirVec += b2Vec2(0, -1);
		}

		if (dirVec.LengthSquared() != 0) {
			dirVec.Normalize();
			dirVec *= velocity;

			float speedDif = (dirVec - rb->getBody()->GetLinearVelocity()).Length();
			appliedForce = 10 * speedDif * (dirVec - rb->getBody()->GetLinearVelocity());
		}
		else {
			appliedForce.SetZero();
		}
	}
}

