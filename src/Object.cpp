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

template<typename T> T* Object::addComponent() {
	static_assert(std::is_base_of<Component, T>::value, "addComponent : class type must be dedrived from Component");
	unique_ptr<T> newComp = make_unique<T>(this);
	T* res = newComp->get();
	components.push_back(move(newComp));

	game->addCompUpdateListener(res);

	return res;
}