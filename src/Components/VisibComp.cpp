#include "VisibComp.h"

using namespace std;

void VisibComp::update() {
	if (player) {
		getObject()->updatePos(player->getPos());
	}

	setSpriteSize();
}

void VisibComp::extendLight()
{
	clock.restart();
}

void VisibComp::setSpriteSize()
{
	float elapsed = clock.getElapsedTime().asSeconds();

	float scale = sprite->getSprite()->getScale().x;
	float nScale;

	if (elapsed < extendTime) {
		nScale = lerp(scale, lightSizeFact, elapsed / extendTime);
	}
	else if (elapsed < extendTime + bonusTime) {
		nScale = lerp(lightSizeFact, 1, (elapsed - extendTime) / bonusTime);
	}
	else {
		nScale = 1;
	}

	sprite->setScale(sf::Vector2f(nScale, nScale));
}
