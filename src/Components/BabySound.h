#pragma once

#include "Component.h"
#include "SFML/Audio.hpp"
#include "Game.h"

class BabySound : public Component {
public:
	using Component::Component;

	void init() override;
	void update() override;

	void restartClock();

private:
	float minDistance = BASE_SIZE * 5;
	float attenuation = 1;
	float minTime = 5;
	float maxTime = 10;
	float waitTime;

	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Clock clock;
};