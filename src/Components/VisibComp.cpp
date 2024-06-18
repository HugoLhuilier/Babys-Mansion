#include "VisibComp.h"

using namespace std;

void VisibComp::update() {
	if (player) {
		getObject()->updatePos(player->getPos());
	}
}
