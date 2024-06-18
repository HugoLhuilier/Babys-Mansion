#pragma once

#include "BaseState.h"
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

/*
* State active when the baby follows the player
*/
class FollowingState : public BaseState {
public:
	void start() override;
	void update() override;

private:
	float minTime = 10;
	float maxTime = 30;
	float waitTime;
	sf::Clock clock;
};