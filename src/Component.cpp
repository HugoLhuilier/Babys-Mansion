#include "Component.h"
#include "Object.h"
#include <iostream>

using namespace std;


Component::Component(Object* nObject) {
	object = nObject;
}

void Component::update() {
}

void Component::init() {
}

void Component::updatePos(sf::Vector2f) {
}

