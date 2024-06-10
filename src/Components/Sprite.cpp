#include "Sprite.h"
#include "Game.h"
#include "Object.h"
#include <iostream>

using namespace std;

void Sprite::setTexture(sf::Texture* tex)
{
	texture = tex;

	sprite.setTexture(*texture);
}

void Sprite::renderSprite() {
	if (win)
		win->draw(sprite);
}

void Sprite::updatePos(sf::Vector2f nPos)
{
	sprite.setPosition(nPos);
	cout << "Sprite updatePos" << endl;
}

void Sprite::updateLayer(int nLayer) {
	Game* game = getObject()->getGame();

	if (layer != INT_MIN) {
		game->deleteSprite(layer, this);
	}

	layer = nLayer;
	game->addSprite(nLayer, this);
}

void Sprite::init()
{
	win = object->getGame()->getWindow();
	cout << "Sprite init" << endl;
}
