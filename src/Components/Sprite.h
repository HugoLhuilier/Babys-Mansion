#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"


class Sprite : public Component {
public:
	using Component::Component;

	void setTexture(sf::Texture* tex, sf::Vector2f size = sf::Vector2f(0, 0));
	void updatePos(sf::Vector2f) override;
	void renderSprite();
	void updateLayer(int nLayer);
	void init() override;

	void setOrigin(sf::Vector2f newOrig);

private:
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::RenderWindow* win;
	int layer = INT_MIN;
};