#pragma once

#include "Object.h"

class AudioListener : public Component {
public:
	using Component::Component;

	void init() override;
	void update() override;
};