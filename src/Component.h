#pragma once

//#include "Object.h"
#include<SFML/Graphics.hpp>

class Object;

class Component {
public:
    Component(Object* nObject);
    virtual void update();
    virtual void init();
    virtual void updatePos(sf::Vector2f);

    Object* getObject() const { return object; }

protected:
    Object* object;
};