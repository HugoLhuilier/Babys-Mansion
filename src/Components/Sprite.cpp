#include "Sprite.h"
#include "Game.h"
#include "Object.h"
#include <iostream>

using namespace std;

void Sprite::setTexture(sf::Texture* tex, sf::Vector2f size) {
	textures.push_back(tex);

	if (textures.size() == 1)
		sprite.setTexture(*tex);
	
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
}

void Sprite::switchSpriteID(int id)
{
	if (id == textureID)
		return;

	if (id >= textures.size()) {
		cerr << "Texture ID out of range" << endl;
		return;
	}

	textureID = id;
	sprite.setTexture(*textures[id]);
}

void Sprite::setOrigin(sf::Vector2f newOrig) {
	sprite.setOrigin(newOrig);
}
