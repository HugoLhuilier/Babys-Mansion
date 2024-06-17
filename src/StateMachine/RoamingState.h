#pragma once

#include "BaseState.h"
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

class RoamingState : public BaseState {
public:
	void start() override;
	void update() override;

private:
	float minTime = 2;
	float maxTime = 5;
	float waitTime;
	b2Vec2 roamDir;
	sf::Clock clock;
};