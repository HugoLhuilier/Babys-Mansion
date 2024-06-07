#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"
#include <vector>


class Game {
public:
    void startGame();
    void update();
private:
    sf::RenderWindow win;
    std::vector<Object> objects;
};