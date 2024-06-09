#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//class Component;
class Game;

class Object {
    using comp_t = std::vector<std::unique_ptr<Component>>;

public:
    Object(sf::Vector2f nPos, Game* nGame);

    comp_t::iterator compBegin() { return components.begin(); }
    comp_t::iterator compEnd() { return components.end(); }

    template<typename T> T* addComponent();
    void addTag(const std::string& tag);
    const bool hasTag(const std::string& tag);

    const sf::Vector2f getPos() { return pos; }
    const Game* getGame() { return game; }

private:
    sf::Vector2f pos;
    comp_t components;
    std::vector<std::string> tags;
    Game* game;
};