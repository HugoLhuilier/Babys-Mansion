#pragma once

#include "Component.h"

class UsableItem : public Component {
public:
	virtual void actionOnUse() = 0;
};