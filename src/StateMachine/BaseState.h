#pragma once

class BabyController;

/*
* Base class for a state for the state machine
*/

class BaseState {
public:
	/*
	* Executed when entering the state
	*/
	virtual void start() = 0;

	/*
	* Executed once per update, when the state is active
	*/
	virtual void update() = 0;

	void setController(BabyController* nCont) { controller = nCont; }

protected:
	BabyController* controller;
};