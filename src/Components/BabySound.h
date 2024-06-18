#pragma once

#include "Component.h"
#include "SFML/Audio.hpp"
#include "Game.h"

/*
* class to manage the sound of the baby every 10 to 20 seconds
*/
class BabySound : public Component {
public:
	using Component::Component;

	/*
	* Function initializing BabySound
	*/
	void init() override;

	/*
	* Function updating BabySound according to the baby position (in order to make spatial sound)
	*/
	void update() override;

	/*
	* Function restarting the clock
	*/
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