#pragma once

#include "Object.h"

class SoundManager : public Component {
public:
	void setListener(Object* nListener);
	void update() override;

private:
	Object* listener;
};