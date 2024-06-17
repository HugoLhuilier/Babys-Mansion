#include "BabySound.h"
#include "Object.h"
#include <iostream>

using namespace std;

void BabySound::init()
{
	if (!buffer.loadFromFile("resources/sounds/SadicBaby.ogg")) {
		cerr << "Failed loading baby sound" << endl;
	}

	sound.setBuffer(buffer);
	sound.setMinDistance(minDistance);
	sound.setAttenuation(attenuation);
	restartClock();
}

void BabySound::update()
{
	sf::Vector2f pos = getObject()->getPos();
	sound.setPosition(pos.x, 0, pos.y);

	if (clock.getElapsedTime().asSeconds() > waitTime) {
		sound.play();
		restartClock();
	}
}

void BabySound::restartClock()
{
	waitTime = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (maxTime - minTime) + minTime;
	clock.restart();
	cout << "Baby sound clock restarted for " << waitTime << " seconds" << endl;
}
