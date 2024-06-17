#pragma once

#include "BaseState.h"
#include <SFML/Graphics.hpp>

class IdleState : public BaseState {
public:
	void start() override;
	void update() override;

private:
	float minTime = 1;
	float maxTime = 5;
	float waitTime;
	sf::Clock clock;
	float followStateProba = 0.5;
};