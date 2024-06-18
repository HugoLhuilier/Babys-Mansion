#pragma once

#include <SFML/Graphics.hpp>
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

/*
* The Game class is used to create the game and  everything within
*/
class Game {
public:
    /*
    * Function to construct a Game
    */
    Game(const sf::VideoMode& vMode);

    /*
    * Function starting the game
    */
    void startGame();

    /*
    * Function adding a sprite to the multimap spriteLayers
    */
    void addSprite(int lay, Sprite* sprite);

    /*
    * Function deleting a sprite from the multimap spriteLayers
    */
    void deleteSprite(int lay, Sprite* sprite);

    /*
    * Function creating an Object at the position pos 
    */
    Object* createObject(sf::Vector2f pos);

    /*
    * Add a Component to the vector of components listener
    * This vector is used for the design pattern "Observer" 
    * When the update() function from game is called, all of the update() functions 
    * from the compUpdateListeners vector will be called too
    */
    void addCompUpdateListener(Component* listener);

    /*
    * Function drawing every sprites by calling renderSprite from "Sprites.h"
    */
    void drawSprites();

    /*
    * Function updating the game that calls all the listeners' update function according to the pattern design "observer"
    */
    void update(); 

    /*
    * Function to stop the game when the baby gets to the player
    */
    void lose();

    /*
    * Function returning a pointer to the texture from the map according to the ID in argument
    */
    sf::Texture* getTexture(int textID) { return &mapTextures[textID]; }

    /*
    * Function returning a pointer to the lantern texture (needed to create the object with its sprite in "Object.h")
    */
    sf::Texture* getTextureLantern() { return &textures[4]; }

    /*
    * Function setting the new player controller
    */
    void setPlayerCtrl(PlayerController* nPC);

    /*
    * Function returning a pointer to the window
    */
    sf::RenderWindow* getWindow() const { return win.get(); }

    /*
    * Function returning a pointer to the world variable from box2d
    */
    b2World* getWorld() const { return world.get(); }
    Object* getFirstObject() const { return objects[0].get(); }

    /*
    * Destructor of the class Game, redefined because of circulary dependencies
    */
    ~Game();

private:
    std::unique_ptr<sf::RenderWindow> win;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<Component*> compUpdateListeners;
    std::multimap<int, Sprite*> spriteLayers;
    std::vector<sf::Texture> textures;
    std::vector<sf::Texture> mapTextures;
    ContactListener contactListener;


    // Component to which instructions will be sent when moving the player (initialized to the last PlayerController componnent attached)
    PlayerController* playerCtrl;

    std::unique_ptr<b2World> world;

    /*
    * Function to handle events like closing the window
    */
    void handleEvents();

    /*
    * Function building the scene for example by creating the player 
    */
    void buildScene();

    /*
    * Function loading the textures of the player, the baby and the visibility 
    */
    void loadTextures();

    /*
    * Function loading the texture for the map
    */
    void loadMap();
};