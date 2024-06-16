#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Game.h"

//class Game;
//class Component;

class Object {
    using comp_t = std::vector<std::unique_ptr<Component>>;

public:
    Object(sf::Vector2f nPos, Game* nGame);

    comp_t::iterator compBegin() { return components.begin(); }
    comp_t::iterator compEnd() { return components.end(); }

    template<typename T> T* addComponent();
    void addTag(const std::string& tag);
    const bool hasTag(const std::string& tag);

    const sf::Vector2f getPos() const { return pos; }
    Game* getGame() const { return game; }

    void updatePos(sf::Vector2f newPos);

private:
    sf::Vector2f pos;
    comp_t components;
    std::vector<std::string> tags;
    Game* game;
};

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