#pragma once

//#include "Object.h"

class Object;

class Component {
public:
    Component(Object* nObject);
    virtual void update() = 0;
    virtual void init() = 0;

    const Object* getObject(){ return object; }

protected:
    Object* object;
};