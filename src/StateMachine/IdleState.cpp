#include "IdleState.h"
#include "Components/BabyController.h"
#include <iostream>

using namespace std;

void IdleState::start()
{
	waitTime = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (maxTime - minTime) + minTime;
	clock.restart();

	cout << "Entering Idle state for " << waitTime << "s" << endl;
}

void IdleState::update()
{
	if (clock.getElapsedTime().asSeconds() > waitTime) {
		if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < followStateProba)
			controller->switchState(StateTag::Following);
		else
			controller->switchState(StateTag::Roaming);
	}
	else {
		b2Vec2 appliedForce = - (controller->getSpeed()) * controller->getRb()->getBody()->GetLinearVelocity();
		controller->getRb()->addForce(appliedForce);
	}
}
