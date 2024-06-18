#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include <vector>


class Sprite : public Component {
public:
	using Component::Component;

	void setTexture(sf::Texture* tex, sf::Vector2f size = sf::Vector2f(0, 0));
	void updatePos(sf::Vector2f) override;
	void renderSprite();
	void updateLayer(int nLayer);
	void init() override;

	void switchSpriteID(int id);

	void setOrigin(sf::Vector2f newOrig);
	void setScale(sf::Vector2f nScale) { sprite.setScale(nScale); }

	const sf::Sprite* getSprite() { return &sprite; }

private:
	sf::Sprite sprite;
	std::vector<sf::Texture*> textures;
	sf::RenderWindow* win;
	int layer = INT_MIN;
	int textureID = 0;
};