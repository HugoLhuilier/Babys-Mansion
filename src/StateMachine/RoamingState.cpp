#include "RoamingState.h"
#include "Components/BabyController.h"

#include <numbers>
#include <cmath>
#include <iostream>

using namespace std;

void RoamingState::start() {
	waitTime = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (maxTime - minTime) + minTime;
	float angle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2 * numbers::pi, speed = controller->getSpeed();
	roamDir = b2Vec2(speed * cos(angle), speed * sin(angle));
	clock.restart();

	cout << "Entering Roaming state for " << waitTime << "s" << endl;
}

void RoamingState::update() {
	if (clock.getElapsedTime().asSeconds() > waitTime) {
		controller->switchState(StateTag::Idle);
	} else {
		float speedDif = controller->getSpeed() - controller->getRb()->getBody()->GetLinearVelocity().Length();

		b2Vec2 appliedForce = 10 * speedDif * roamDir;
		controller->getRb()->addForce(appliedForce);
	}
}
