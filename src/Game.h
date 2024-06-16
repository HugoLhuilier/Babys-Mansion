#pragma once

#include <SFML/Graphics.hpp>
//#include "Object.h"
#include <vector>
#include "Component.h"

#define GAME_NAME "Baby's Mansion"

class Object;
class Sprite;

class Game {
public:
    Game(const sf::VideoMode& vMode);
    void startGame();
    void addSprite(int lay, Sprite* sprite);
    void deleteSprite(int lay, Sprite* sprite);
    Object* createObject(sf::Vector2f pos);
    void addCompUpdateListener(Component* listener);
    void drawSprites();

    sf::RenderWindow* getWindow() const { return win.get(); }

    ~Game();

private:
    std::unique_ptr<sf::RenderWindow> win;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<Component*> compUpdateListeners;
    std::multimap<int, Sprite*> spriteLayers;
    std::vector<sf::Texture> textures;

    void update();
    void handleEvents();
    void buildScene();
    void loadTextures();
    void loadMap();
};