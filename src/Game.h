#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Component.h"
#include "box2d/box2d.h"
#include "ContactListener.h"

#define GAME_NAME "Baby's Mansion"
#define BASE_SIZE 8
#define PLAYER_SPEED 50

class Object;
class Sprite;
class PlayerController;

enum class GameState {
    Playing,
    Lose,
    Waiting,
    Win
};

class Game {
public:
    Game(const sf::VideoMode& vMode);
    void startGame();
    void addSprite(int lay, Sprite* sprite);
    void deleteSprite(int lay, Sprite* sprite);
    Object* createObject(sf::Vector2f pos);
    void addCompUpdateListener(Component* listener);
    void drawSprites();

    void winning();
    void lose();
    void reloadGame();

    sf::Texture* getTexture(int textID) { return &mapTextures[textID]; }
    sf::Texture* getTextureLantern() { return &textures[4]; }
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
    std::vector<sf::Texture> mapTextures;
    ContactListener contactListener;
    GameState state = GameState::Waiting;

    sf::SoundBuffer loseBuffer;
    sf::SoundBuffer winBuffer;
    sf::Sound loseSound;
    sf::Sound winSound;
    sf::Music music;


    // Component to which instructions will be sent when moving the player (initialized to the last PlayerController componnent attached)
    PlayerController* playerCtrl;

    std::unique_ptr<b2World> world;

    void update();
    void handleEvents();
    void buildScene();
    void loadTextures();
    void loadMap();
};