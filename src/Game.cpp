#include "Game.h"
#include "Components/Sprite.h"
#include "Components/PlayerController.h"
#include "Object.h"
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/TileSet.hpp>
#include "Components/CameraController.h"
#include "Components/BabyController.h"
#include "Components/SoundManager.h"
#include "Components/BabySound.h"

using namespace std;

Game::Game(const sf::VideoMode &vMode)
{
	win = make_unique<sf::RenderWindow>(vMode, GAME_NAME);
	win->setVerticalSyncEnabled(true);

	sf::View view = win->getView();
	view.zoom(0.1);
	win->setView(view);

	b2Vec2 grav(0, 0);
	world = make_unique<b2World>(grav);
	world->SetContactListener(&contactListener);
}

Game::~Game() {}

void Game::loadTextures() {
	sf::Texture text;
	if (!text.loadFromFile("resources/sprites/test/salut!.png")) {
		cerr << "Can't load texture" << endl;
	}
	textures.push_back(text);

	tmx::Map map;
	if (!map.load("resources/TileMap/test/test.tmx")) {
		std::cerr << "Failed to load the map" << std::endl;
	}
	// Get the tileset 
	const auto& tilesets = map.getTilesets();
	if (tilesets.empty()) {
		std::cerr << "No tilesets found in the map" << std::endl;
	}

	const auto& tileset = tilesets[0];
	int tileWidth = tileset.getTileSize().x;
	int tileHeight = tileset.getTileSize().y;
	

	// Load the tileset texture
	sf::Texture tilesetTexture; 
	if (!tilesetTexture.loadFromFile("resources/TileMap/test/4 BigSet.png")) {
		std::cerr << "Failed to load tileset texture" << std::endl;
	}
	int nbTile_x = tilesetTexture.getSize().x / tileWidth;
	int nbTile_y = tilesetTexture.getSize().y / tileHeight;
	mapTextures.reserve(nbTile_x*nbTile_y);

	
	for (auto y = 0; y < nbTile_y; y++) {
		for (auto x = 0; x < nbTile_x; x++) {
			sf::Texture tileTexture;
			
			if (!tileTexture.loadFromFile("resources/TileMap/test/4 BigSet.png", sf::IntRect(x * tileWidth, y * tileHeight, 16, 16))) {
				std::cerr << "Failed to add to textures" << std::endl;
			}
			mapTextures.push_back(tileTexture);
		}
	}
	if (!text.loadFromFile("resources/sprites/player/player_dos.png")) {
		cerr << "Can't load texture" << endl;
	}
	textures.push_back(text);

	if (!text.loadFromFile("resources/sprites/baby/baby_gauche.png")) {
		cerr << "Can't load texture" << endl;
	}
	textures.push_back(text);
}

void Game::startGame()
{
	loadTextures();
	loadMap(); 
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
	box.SetAsBox(BASE_SIZE/2, BASE_SIZE/2);

	//Object* testObject = createObject(sf::Vector2f(0, 0));
	//Sprite* spriteComp = testObject->addComponent<Sprite>();
	//RigidBody* rb1 = testObject->addComponent<RigidBody>();
	//rb1->createBody(b2_staticBody);
	//rb1->addFixture(box);

	//Object* testObject2 = createObject(sf::Vector2f(32, 0));
	//Sprite* spriteComp2 = testObject2->addComponent<Sprite>();
	//RigidBody* rb2 = testObject2->addComponent<RigidBody>();
	//rb2->createBody(b2_staticBody);
	//rb2->addFixture(box);

	//Object* testObject3 = createObject(sf::Vector2f(16, 16));
	//Sprite* spriteComp3 = testObject3->addComponent<Sprite>();
	//RigidBody* rb3 = testObject3->addComponent<RigidBody>();
	//rb3->createBody(b2_staticBody);
	//rb3->addFixture(box);

	//spriteComp->updateLayer(0);
	//spriteComp->setTexture(&textures[0]);
	//spriteComp2->updateLayer(0);
	//spriteComp2->setTexture(&textures[0]);
	//spriteComp3->updateLayer(-1);
	//spriteComp3->setTexture(&textures[0]);

	Object* player = createObject(sf::Vector2f(0, 0));
	PlayerController* playCtrl = player->addComponent<PlayerController>();
	RigidBody* rb = player->addComponent<RigidBody>();
	rb->createBody(b2BodyType::b2_dynamicBody);
	AudioListener* audio = player->addComponent<AudioListener>();
	player->addTag(Tag::Player);
	
	fix.shape = &box;
	fix.density = 1;
	fix.friction = 0.3f;
	rb->addFixture(fix);
	playCtrl->setRb(rb);
	Sprite* playerSprite = player->addComponent<Sprite>();
	playerSprite->updateLayer(5);
	playerSprite->setTexture(&textures[1], sf::Vector2f(BASE_SIZE, BASE_SIZE));

	Object* cam = createObject(sf::Vector2f(0, 0));
	CameraController* camC = cam->addComponent<CameraController>();
	camC->setPlayer(player);
	sf::Vector2f low(0, 0), up(500, 500);
	camC->setBounds(low, up);

	Object* fantome = createObject(sf::Vector2f(0, 0));
	Sprite* fantSprite = fantome->addComponent<Sprite>();
	fantSprite->updateLayer(5);
	fantSprite->setTexture(&textures[2], sf::Vector2f(BASE_SIZE, BASE_SIZE));
	RigidBody* rbFant = fantome->addComponent<RigidBody>();
	fix.isSensor = true;
	rbFant->createBody(b2BodyType::b2_dynamicBody);
	rbFant->addFixture(fix);
	BabyController* cont = fantome->addComponent<BabyController>();
	cont->setPlayer(player);
	cont->setRb(rbFant);
	BabySound* sound = fantome->addComponent<BabySound>();
	fantome->addTag(Tag::Baby);
}

void Game::drawSprites() {
	for (auto& layer : spriteLayers) {
		layer.second->renderSprite();
	}

	win->display();
}

void Game::lose()
{
	cout << "Perdu !!" << endl;
}

void Game::loadMap() {
	tmx::Map map;
	if (!map.load("resources/TileMap/test/test.tmx")) {
		std::cerr << "Failed to load the map" << std::endl;
	}

	// Get the map size in tiles
	auto mapSize = map.getTileCount();

	// Iterate through the layers
	const auto& layers = map.getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Tile) {
			const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
			string name = layer->getName();

			// Iterate through the tiles
			const auto& tiles = tileLayer.getTiles();
			for (unsigned y = 0; y < mapSize.y; ++y) {
				for (unsigned x = 0; x < mapSize.x; ++x) {
					auto tileID = tiles[y * mapSize.x + x].ID;
					if (tileID == 0) continue; // Skip empty tiles

					// Adjust the tileID to match the texture coordinates
					tileID--;

					sf::Vector2f pos(x * BASE_SIZE, y * BASE_SIZE);
					Object* tuile = createObject(pos);

					if (name == "wall") {
						tuile->makeItWall(tileID);
					} else if (name == "floor") {
						tuile->makeItFloor(tileID);
					}
					else if (name == "furniture") {
						tuile->makeItFurniture(tileID);
					}
					
				}
			}
		}
	}
}


void Game::setPlayerCtrl(PlayerController* nPC) {
	playerCtrl = nPC;
}