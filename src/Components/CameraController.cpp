#include "Object.h"
#include "Game.h"
#include "CameraController.h"

using namespace std;

void CameraController::update()
{
	if (player) {
		sf::View nView = win->getView();
		nView.setCenter(player->getPos());
	}
}

void CameraController::init() {
	win = object->getGame()->getWindow();
}