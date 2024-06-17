#include "Object.h"
#include "Component.h"
#include "Game.h"
#include "Components/Sprite.h"
#include "Components/RigidBody.h"
#include <iostream>

using namespace std;


Object::Object(sf::Vector2f nPos, Game* nGame)
{
	pos = nPos;
	game = nGame;
}

void Object::addTag(const std::string& tag)
{
	tags.push_back(tag);
}

const bool Object::hasTag(const std::string& tag)
{
	for (string str : tags) {
		if (str == tag)
			return true;
	}

	return false;
}

void Object::updatePos(sf::Vector2f newPos) {
	pos = newPos;

	for (const auto& comp : components) {
		comp->updatePos(newPos);
	}
}

void Object::makeItWall(int textID) {
	Sprite* sprite = addComponent<Sprite>();
	sprite->updateLayer(0);
	sprite->setTexture(game->getTexture(textID));

	b2FixtureDef fix; 
	b2PolygonShape box; 
	box.SetAsBox(4, 4);

	RigidBody* rb = addComponent<RigidBody>(); 
	rb->createBody(b2_staticBody); 
	rb->addFixture(box); 
}

void Object::makeItFloor(int textID) {
	Sprite* sprite = addComponent<Sprite>(); 
	sprite->updateLayer(-1); 
	sprite->setTexture(game->getTexture(textID)); 
}

void Object::makeItFurniture(int textID) {
	Sprite* sprite = addComponent<Sprite>(); 
	sprite->updateLayer(0); 
	sprite->setTexture(game->getTexture(textID)); 

	b2FixtureDef fix; 
	b2PolygonShape box; 
	box.SetAsBox(4, 4); 

	RigidBody* rb = addComponent<RigidBody>(); 
	rb->createBody(b2_staticBody); 
	rb->addFixture(box); 
}
