#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include <vector>

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