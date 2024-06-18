#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

/*
* class Sprite used to put a sprite on an object and set/update its characteristics
*/
class Sprite : public Component {
public:
	using Component::Component;

	/*
	* Function setting the texture
	*/
	void setTexture(sf::Texture* tex, sf::Vector2f size = sf::Vector2f(0, 0));

	/*
	* Function updating the position
	*/
	void updatePos(sf::Vector2f) override;

	/*
	* Function calling win::draw(sorite) to draw a sprite
	*/
	void renderSprite();

	/*
	* Function udating the sprite's layer
	*/
	void updateLayer(int nLayer);

	/*
	* Function initialazing the sprite
	*/
	void init() override;

	/*
	* Function setting the origin of the sprite
	*/
	void setOrigin(sf::Vector2f newOrig);

private:
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::RenderWindow* win;
	int layer = INT_MIN;
};