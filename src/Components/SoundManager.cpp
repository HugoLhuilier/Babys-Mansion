#include "SoundManager.h"
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

void AudioListener::init() {
	sf::Listener::setDirection(0, 0, -1);
	cout << "AudioListener initialized" << endl;
}

void AudioListener::update() {
	sf::Vector2f pos = object->getPos();
	sf::Listener::setPosition(pos.x, 0, pos.y);
}
