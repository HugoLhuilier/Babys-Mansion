#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//class Component;

class Object {
public:

private:
    sf::Vector2f pos;
    std::vector<Component> components;
    std::vector<std::string> tags;
};