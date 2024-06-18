#pragma once

#include<SFML/Graphics.hpp>

class Object;

/*
* Class component to give charecteristics to the object 
*/
class Component {
public:
    /*
    * Function constructing a component
    */
    Component(Object* nObject);

    /*
    * Function updating a component, different according to the component's type
    */
    virtual void update();

    /*
    * Function initiating the component, different according to its type
    */
    virtual void init();

    /*
    * Function updating the position, different according to the component's type
    */
    virtual void updatePos(sf::Vector2f);

    /*
    * Function returning a pointer to the object
    */
    Object* getObject() const { return object; }

protected:
    Object* object;
};