#pragma once

#include "Component.h"

class TestComp : public Component {
public:
	using Component::Component;

	void update() override;
	int getNbUpdate() { return nbUpdate; }

private:
	int nbUpdate = 0;
};