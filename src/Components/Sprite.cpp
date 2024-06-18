#include "Sprite.h"
#include "Game.h"
#include "Object.h"
#include <iostream>

using namespace std;

void Sprite::setTexture(sf::Texture* tex, sf::Vector2f size) {
	texture = tex;

	sprite.setTexture(*texture);
	
	if (size != sf::Vector2f(0, 0)) {
		sprite.setScale(sf::Vector2f(size.x / tex->getSize().x, size.y / tex->getSize().y));
	}
}

void Sprite::renderSprite() {
	if (win)
		win->draw(sprite);
}

void Sprite::updatePos(sf::Vector2f nPos) {
	sprite.setPosition(nPos);
}

void Sprite::updateLayer(int nLayer) {
	Game* game = getObject()->getGame();

	if (layer != INT_MIN) {
		game->deleteSprite(layer, this);
	}

	layer = nLayer;
	game->addSprite(nLayer, this);
}

void Sprite::init() {
	win = object->getGame()->getWindow();
	cout << "Sprite init" << endl;
}

void Sprite::setOrigin(sf::Vector2f newOrig) {
	sprite.setOrigin(newOrig);
}
