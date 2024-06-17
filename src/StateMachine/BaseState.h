#pragma once

class BabyController;

class BaseState {
public:
	virtual void start() = 0;
	virtual void update() = 0;

	void setController(BabyController* nCont) { controller = nCont; }

protected:
	BabyController* controller;
};