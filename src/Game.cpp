#include "Game.h"
#include "Components/Sprite.h"
#include "Object.h"
#include <iostream>

using namespace std;

Game::Game(const sf::VideoMode &vMode)
{
	win = make_unique<sf::RenderWindow>(vMode, GAME_NAME);
	win->setVerticalSyncEnabled(true);
}

Game::~Game() {}

void Game::loadTextures() {
	sf::Texture text;
	if (!text.loadFromFile("resources/sprites/test/salut!.png")) {
		cerr << "Can't load texture" << endl;
	}
	textures.push_back(text);
}

void Game::startGame()
{
	loadTextures();
	buildScene();

	while (win->isOpen()) {
		win->clear();

		handleEvents();

		update();

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
	Object* testObject = createObject(sf::Vector2f(0, 0));
	Sprite* spriteComp = testObject->addComponent<Sprite>();

	Object* testObject2 = createObject(sf::Vector2f(32, 0));
	Sprite* spriteComp2 = testObject2->addComponent<Sprite>();

	Object* testObject3 = createObject(sf::Vector2f(16, 16));
	Sprite* spriteComp3 = testObject3->addComponent<Sprite>();

	spriteComp->updateLayer(0);
	spriteComp->setTexture(&textures[0]);
	spriteComp2->updateLayer(0);
	spriteComp2->setTexture(&textures[0]);
	spriteComp3->updateLayer(-1);
	spriteComp3->setTexture(&textures[0]);
}

void Game::drawSprites() {
	for (auto& layer : spriteLayers) {
		layer.second->renderSprite();
	}

	win->display();
}