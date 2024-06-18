#include "Object.h"
#include "Component.h"
#include "Game.h"
#include "Components/Sprite.h"
#include "Components/RigidBody.h"
#include <iostream>
#include "Components/CameraController.h"
#include "Components/SoundManager.h"
#include "Components/PlayerController.h"
#include <SFML/Graphics.hpp>
#include "Components/BabyController.h"
#include "Components/BabySound.h"
#include "Components/VisibComp.h"

using namespace std;


Object::Object(sf::Vector2f nPos, Game* nGame) {
	pos = nPos;
	game = nGame;
}

void Object::addTag(const Tag tag) {
	tags.push_back(tag);
}

const bool Object::hasTag(const Tag tag) {
	for (auto str : tags) {
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
	sprite->setTexture(game->getTexture(textID), sf::Vector2f(BASE_SIZE, BASE_SIZE));

	b2PolygonShape box; 
	box.SetAsBox(BASE_SIZE/2, BASE_SIZE/2);

	RigidBody* rb = addComponent<RigidBody>(); 
	rb->createBody(b2_staticBody); 
	rb->addFixture(box); 
}

void Object::makeItFloor(int textID) {
	Sprite* sprite = addComponent<Sprite>(); 
	sprite->updateLayer(-1); 
	sprite->setTexture(game->getTexture(textID), sf::Vector2f(BASE_SIZE, BASE_SIZE));
}

void Object::makeItFurniture(int textID) {
	Sprite* sprite = addComponent<Sprite>(); 
	sprite->updateLayer(0); 
	sprite->setTexture(game->getTexture(textID), sf::Vector2f(BASE_SIZE, BASE_SIZE));

	b2FixtureDef fix; 
	b2PolygonShape box; 
	box.SetAsBox(BASE_SIZE / 2, BASE_SIZE / 2);

	RigidBody* rb = addComponent<RigidBody>(); 
	rb->createBody(b2_staticBody); 
	rb->addFixture(box); 
}

void Object::makeItLantern(int textID) {
	Sprite* sprite = addComponent<Sprite>();
	sprite->updateLayer(0);
	sprite->setTexture(game->getTextureLantern(), sf::Vector2f(BASE_SIZE, BASE_SIZE));

	RigidBody* rb = addComponent<RigidBody>();
	b2FixtureDef fix;
	b2PolygonShape box;
	box.SetAsBox(BASE_SIZE / 2, BASE_SIZE / 2);
	fix.shape = &box;
	fix.isSensor = true;
	rb->createBody(b2_staticBody);
	rb->addFixture(fix);

	addTag(Tag::Lantern);
}

void Object::makeItFinish(int textID) {
	Sprite* sprite = addComponent<Sprite>();
	sprite->updateLayer(-1);
	sprite->setTexture(game->getTexture(textID), sf::Vector2f(BASE_SIZE, BASE_SIZE));

	RigidBody* rb = addComponent<RigidBody>();
	b2FixtureDef fix;
	b2PolygonShape box;
	box.SetAsBox(BASE_SIZE / 2, BASE_SIZE / 2);
	fix.shape = &box;
	fix.isSensor = true;
	rb->createBody(b2_staticBody);
	rb->addFixture(fix);

	addTag(Tag::Finnish);
}

void Object::makeItCamera(Object* player) {
	CameraController* camC = addComponent<CameraController>();
	camC->setPlayer(player);
	sf::Vector2f low(FLT_MIN, FLT_MIN), up(FLT_MAX, FLT_MAX);
	camC->setBounds(low, up);
}

void Object::makeItPlayer(sf::Texture* text[4]) {
	Sprite* playerSprite = addComponent<Sprite>();
	playerSprite->updateLayer(5);
	sf::Vector2f spriteSize(BASE_SIZE * 2 / 3, BASE_SIZE * 80 / 48);
	playerSprite->setTexture(text[0], spriteSize);
	playerSprite->setTexture(text[1], spriteSize);
	playerSprite->setTexture(text[2], spriteSize);
	playerSprite->setTexture(text[3], spriteSize);

	PlayerController* playCtrl = addComponent<PlayerController>();
	RigidBody* rb = addComponent<RigidBody>();
	b2FixtureDef fix;
	b2PolygonShape box;
	box.SetAsBox(spriteSize.x / 2, spriteSize.y / 4, b2Vec2(- 1 * spriteSize.x / 4, spriteSize.y / 2), 0);
	fix.shape = &box;
	fix.density = 1;
	fix.friction = 0.3f;
	rb->createBody(b2BodyType::b2_dynamicBody);
	rb->addFixture(fix);
	playCtrl->setRb(rb);
	playCtrl->setSprite(playerSprite);

	AudioListener* audio = addComponent<AudioListener>();
	addTag(Tag::Player);
}

void Object::makeItBaby(sf::Texture* text[], Object* player) {
	b2FixtureDef fix;
	b2PolygonShape box;
	box.SetAsBox(BASE_SIZE / 2, BASE_SIZE / 2);
	fix.shape = &box;
	fix.density = 1;

	fix.friction = 0.3f;
	Sprite* fantSprite = addComponent<Sprite>();
	fantSprite->updateLayer(5);
	fantSprite->setTexture(text[0], sf::Vector2f(BASE_SIZE, BASE_SIZE));
	fantSprite->setTexture(text[1], sf::Vector2f(BASE_SIZE, BASE_SIZE));
	RigidBody* rbFant = addComponent<RigidBody>();
	fix.isSensor = true;
	rbFant->createBody(b2BodyType::b2_dynamicBody);
	rbFant->addFixture(fix);
	BabyController* cont = addComponent<BabyController>();
	cont->setPlayer(player);
	cont->setRb(rbFant);
	cont->setSprite(fantSprite);
	BabySound* sound = addComponent<BabySound>();
	addTag(Tag::Baby);
}

void Object::makeItVisibility(sf::Texture* text, Object* player) {
	Sprite* visibSprite = addComponent<Sprite>();
	visibSprite->updateLayer(INT_MAX);
	visibSprite->setTexture(text);
	visibSprite->setOrigin(sf::Vector2f(120, 120));
	VisibComp* visibComp = addComponent<VisibComp>();
	visibComp->setPlayer(player);
	visibComp->setSprite(visibSprite);
}