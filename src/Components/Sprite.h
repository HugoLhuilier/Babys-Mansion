#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"


class Sprite : public Component {
public:
	using Component::Component;

	void setTexture(sf::Texture* tex);
	void updatePos(sf::Vector2f) override;
	void renderSprite();
	void updateLayer(int nLayer);
	void init() override;

private:
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::RenderWindow* win;
	int layer = INT_MIN;
};