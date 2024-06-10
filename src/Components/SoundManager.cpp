#include "SoundManager.h"
#include <SFML/Audio.hpp>

void SoundManager::update()
{
	if (listener) {
		sf::Vector2f pos = listener->getPos();
		sf::Listener::setPosition(pos.x, pos.y, 0);
	}
}

void SoundManager::setListener(Object* nListener)
{
	listener = nListener;
}
