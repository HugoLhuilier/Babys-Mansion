#pragma once

#include "Component.h"
#include "Object.h"

class VisibComp : public Component {
public:
	using Component::Component;

	void update() override;

	void setPlayer(Object* nP) { player = nP; }

private:
	Object* player;
};