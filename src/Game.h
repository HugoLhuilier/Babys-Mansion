#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"
#include <vector>

#define GAME_NAME "Baby's Mansion"


class Game {
public:
    Game(const sf::VideoMode& vMode);
    void startGame();

    const sf::RenderWindow* getWindow() { return win.get(); }

private:
    std::unique_ptr<sf::RenderWindow> win;
    std::vector<Object> objects;
    std::vector<Component*> compUpdateListeners;

    void update();
    void addCompUpdateListener(Component* listener);
    void handleEvents();
    void buildscene();
};