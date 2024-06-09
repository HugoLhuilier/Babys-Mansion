#pragma once

#include "Object.h"

class SoundManager : public Component {
public:
	void setListener(const Object* nListener);
	void update() override;

private:
	Object* listener;
};