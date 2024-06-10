#include "Object.h"
#include "Component.h"
#include "Game.h"

using namespace std;


Object::Object(sf::Vector2f nPos, Game* nGame)
{
	pos = nPos;
	game = nGame;
}

void Object::addTag(const std::string& tag)
{
	tags.push_back(tag);
}

const bool Object::hasTag(const std::string& tag)
{
	for (string str : tags) {
		if (str == tag)
			return true;
	}

	return false;
}

void Object::updatePos(sf::Vector2f newPos) {
	pos = newPos;

	for (const auto& comp : components) {
		comp->updatePos(newPos);
	}
}