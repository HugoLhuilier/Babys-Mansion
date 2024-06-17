#include "FollowingState.h"
#include "Components/BabyController.h"
#include "Object.h"

#include <numbers>
#include <cmath>
#include <iostream>

using namespace std;

void FollowingState::start()
{
	waitTime = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (maxTime - minTime) + minTime;
	clock.restart();

	cout << "Entering Following state for " << waitTime << "s" << endl;
}

void FollowingState::update()
{
	if (clock.getElapsedTime().asSeconds() > waitTime) {
		controller->switchState(StateTag::Idle);
	}
	else {
		sf::Vector2f dir = controller->getPlayer()->getPos() - controller->getObject()->getPos();
		b2Vec2 followDir(dir.x, dir.y);
		followDir.Normalize();
		followDir *= controller->getSpeed();
		b2Vec2 appliedForce = followDir - (controller->getSpeed() / 200) * controller->getRb()->getBody()->GetLinearVelocity();
		controller->getRb()->addForce(appliedForce);
	}
}
