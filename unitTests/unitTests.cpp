#include <gtest/gtest.h>
#include "Game.h"
#include "Object.h"
#include "Components/Sprite.h"
#include "Components/TestComp.h"
#include "Components/BabyController.h"
#include "Components/CameraController.h"


TEST(CreationObject, Player) {
	Game game(sf::VideoMode::getFullscreenModes()[0]); 
	Object* player = game.createObject(sf::Vector2f(42 * BASE_SIZE, 62 * BASE_SIZE));
	EXPECT_EQ(game.getFirstObject(), player);	
}

TEST(AddComponent, Sprite) {
	Game game(sf::VideoMode::getFullscreenModes()[0]); 
	Object* player = game.createObject(sf::Vector2f(42 * BASE_SIZE, 62 * BASE_SIZE)); 
	Sprite* sprite = player->addComponent<Sprite>();
	EXPECT_EQ(player->getFirstComponent(), sprite);
}

TEST(UpdateComp, TestComp) {
	Game game(sf::VideoMode::getFullscreenModes()[0]); 
	Object* player = game.createObject(sf::Vector2f(42 * BASE_SIZE, 62 * BASE_SIZE)); 
	TestComp* test = player->addComponent<TestComp>();
	game.update();
	EXPECT_EQ(test->getNbUpdate(), 1);
}

TEST(StateMachine, Baby) {
	Game game(sf::VideoMode::getFullscreenModes()[0]); 
	Object* fantome = game.createObject(sf::Vector2f(0, 0)); 
	BabyController* babyContr = fantome->addComponent<BabyController>(); 
	babyContr->switchState(StateTag::Idle);
	BaseState* state = babyContr->getState();
	EXPECT_EQ(typeid(*state), typeid(IdleState));
}

TEST(UpdateCameraPos, CameraController) {
	Game game(sf::VideoMode::getFullscreenModes()[0]);
	Object* player = game.createObject(sf::Vector2f(42 * BASE_SIZE, 62 * BASE_SIZE));
	CameraController* camera = player->addComponent<CameraController>();
	camera->setPlayer(player);
	sf::Vector2f low(FLT_MIN, FLT_MIN), up(FLT_MAX, FLT_MAX); 
	camera->setBounds(low, up); 
	game.update();
	EXPECT_EQ(player->getPos(), game.getWindow()->getView().getCenter());
	player->updatePos(sf::Vector2f(128, 371));
	game.update(); 
	EXPECT_EQ(player->getPos(), game.getWindow()->getView().getCenter());
}
