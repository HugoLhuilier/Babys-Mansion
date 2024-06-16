#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include "box2d/box2d.h"

#define GAME_NAME "Baby's Mansion"

class Object;
class Sprite;
class PlayerController;

class Game {
public:
    Game(const sf::VideoMode& vMode);
    void startGame();
    void addSprite(int lay, Sprite* sprite);
    void deleteSprite(int lay, Sprite* sprite);
    Object* createObject(sf::Vector2f pos);
    void addCompUpdateListener(Component* listener);
    void drawSprites();

    // Sets the new playerCtrl
    void setPlayerCtrl(PlayerController* nPC);

    sf::RenderWindow* getWindow() const { return win.get(); }
    b2World* getWorld() const { return world.get(); }

    ~Game();

private:
    std::unique_ptr<sf::RenderWindow> win;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<Component*> compUpdateListeners;
    std::multimap<int, Sprite*> spriteLayers;
    std::vector<sf::Texture> textures;

    // Component to which instructions will be sent when moving the player (initialized to the last PlayerController componnent attached)
    PlayerController* playerCtrl;

    std::unique_ptr<b2World> world;

    void update();
    void handleEvents();
    void buildScene();
    void loadTextures();    
};