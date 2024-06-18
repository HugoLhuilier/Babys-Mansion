#include "BabyController.h"

using namespace std;

void BabyController::init() {
	idleState.setController(this);
	roamingState.setController(this);
	followingState.setController(this);

	switchState(StateTag::Idle);
}

void BabyController::update() {
	curState->update();
}

void BabyController::switchState(StateTag newState) {
	switch (newState) {
	case StateTag::Roaming:
		curState = &roamingState;
		break;

	case StateTag::Idle:
		curState = &idleState;
		break;

	default:
		curState = &followingState;
	}

	curState->start();
}
