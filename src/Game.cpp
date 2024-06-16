#include "Game.h"
#include "Components/Sprite.h"
#include "Components/PlayerController.h"
#include "Object.h"
#include <iostream>
#include <tmxlite/Map.hpp>

using namespace std;

Game::Game(const sf::VideoMode &vMode)
{
	win = make_unique<sf::RenderWindow>(vMode, GAME_NAME);
	win->setVerticalSyncEnabled(true);

	b2Vec2 grav(0, 0);
	world = make_unique<b2World>(grav);
}

Game::~Game() {}

void Game::loadTextures() {
	sf::Texture text;
	if (!text.loadFromFile("resources/sprites/test/salut!.png")) {
		cerr << "Can't load texture" << endl;
	}
	textures.push_back(text);

	if (!text.loadFromFile("resources/sprites/test/bonhomme.png")) {
		cerr << "Can't load texture" << endl;
	}
	textures.push_back(text);
}

void Game::startGame()
{
	loadTextures();
	buildScene();

	sf::Clock clock;
	sf::Time elapsed;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	while (win->isOpen()) {
		elapsed = clock.restart();

		win->clear();

		handleEvents();

		update();

		world->Step(elapsed.asSeconds(), velocityIterations, positionIterations);

		drawSprites();
	}
}

void Game::update()
{
	for (auto& comp : compUpdateListeners) {
		comp->update();
	}
}

void Game::addCompUpdateListener(Component* listener)
{
	compUpdateListeners.push_back(listener);
}

void Game::handleEvents()
{
	sf::Event event;

	while (win->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			win->close();
	}
}

void Game::addSprite(int lay, Sprite* sprite) {
	spriteLayers.insert(make_pair(lay, sprite));
}

void Game::deleteSprite(int lay, Sprite* sprite) {
	typedef multimap<int, Sprite*>::iterator iterator;
	pair<iterator, iterator> iterpair = spriteLayers.equal_range(lay);

	iterator it = iterpair.first;
	for (; it != iterpair.second; it++) {
		if (it->second == sprite) {
			spriteLayers.erase(it);
			break;
		}
	}
}

Object* Game::createObject(sf::Vector2f pos) {
	unique_ptr<Object> newObj = make_unique<Object>(pos, this);
	Object* res = newObj.get();
	objects.push_back(move(newObj));

	return res;
}

void Game::buildScene()
{
	b2FixtureDef fix;
	b2PolygonShape box;
	box.SetAsBox(16, 16);

	Object* testObject = createObject(sf::Vector2f(0, 0));
	Sprite* spriteComp = testObject->addComponent<Sprite>();
	RigidBody* rb1 = testObject->addComponent<RigidBody>();
	rb1->createBody(b2_staticBody);
	rb1->addFixture(box);

	Object* testObject2 = createObject(sf::Vector2f(32, 0));
	Sprite* spriteComp2 = testObject2->addComponent<Sprite>();
	RigidBody* rb2 = testObject2->addComponent<RigidBody>();
	rb2->createBody(b2_staticBody);
	rb2->addFixture(box);

	Object* testObject3 = createObject(sf::Vector2f(16, 16));
	Sprite* spriteComp3 = testObject3->addComponent<Sprite>();
	RigidBody* rb3 = testObject3->addComponent<RigidBody>();
	rb3->createBody(b2_staticBody);
	rb3->addFixture(box);

	spriteComp->updateLayer(0);
	spriteComp->setTexture(&textures[0]);
	spriteComp2->updateLayer(0);
	spriteComp2->setTexture(&textures[0]);
	spriteComp3->updateLayer(-1);
	spriteComp3->setTexture(&textures[0]);

	Object* player = createObject(sf::Vector2f(100, 100));
	PlayerController* playCtrl = player->addComponent<PlayerController>();
	RigidBody* rb = player->addComponent<RigidBody>();
	rb->createBody(b2BodyType::b2_dynamicBody);
	
	fix.shape = &box;
	fix.density = 1;
	fix.friction = 0.3f;
	rb->addFixture(fix);
	playCtrl->setRb(rb);
	Sprite* playerSprite = player->addComponent<Sprite>();
	playerSprite->updateLayer(5);
	playerSprite->setTexture(&textures[1]);
}

void Game::drawSprites() {
	for (auto& layer : spriteLayers) {
		layer.second->renderSprite();
	}

	win->display();
}

void Game::setPlayerCtrl(PlayerController* nPC) {
	playerCtrl = nPC;
}