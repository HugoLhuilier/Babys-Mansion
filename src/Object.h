#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Game.h"

/* 
* The tags allow to know the type of object and thus adapt the behavior when two rigid bodies collide
* For example, when the player collide with the baby, the game stops because the player has lost
*/
enum class Tag {
    Player,
    Baby
};

/*
* Class Object, used to define every object on the map, the player, the baby, the camera etc
* Every object is given a vector of component to deal with the different comportements
*/
class Object {
    using comp_t = std::vector<std::unique_ptr<Component>>;

public:
    /*
    * Function to construct an Object 
    */
    Object(sf::Vector2f nPos, Game* nGame);

    /*
    * Function returning the iterator "begin" and "end" of the components vector
    */
    comp_t::iterator compBegin() { return components.begin(); }
    comp_t::iterator compEnd() { return components.end(); }

    /*
    * Function adding a component
    */
    template<typename T> T* addComponent();

    /*
    * Function adding a tag
    */
    void addTag(const Tag tag);

    /*
    * Function to check if the object possesses the Tag tag
    */
    const bool hasTag(const Tag tag);

    /*
    * Function returning the object's position
    */
    const sf::Vector2f getPos() const { return pos; }

    /*
    * Function returning the game
    */
    Game* getGame() const { return game; }

    /*
    * Function updating the object's position
    */
    void updatePos(sf::Vector2f newPos);

    /*
    * the "makeIt" functions are used to give the object some caracteristics
    * for example a wall is a RigidBody, with a Sprite, and is static
    */
    void makeItWall(int textID);
    void makeItFloor(int textID);
    void makeItFurniture(int textID);
    void makeItLantern(int textID); 
    void makeItFinish(int textID);

private:
    sf::Vector2f pos;
    comp_t components;
    std::vector<Tag> tags;
    Game* game;
};

/*
* Template function to add a component to the components vector making sure the type of component exists 
* Then the "addCompUpdateListener" is called to add the component to the listeners for the "Observer" pattern design 
*/
template<typename T>
T* Object::addComponent() {
    static_assert(std::is_base_of<Component, T>::value, "addComponent : class type must be derived from Component");
    std::unique_ptr<T> newComp = std::make_unique<T>(this);
    T* res = newComp.get();
    components.push_back(std::move(newComp));

    game->addCompUpdateListener(res);

    res->init();
    res->updatePos(pos);

    return res;
}