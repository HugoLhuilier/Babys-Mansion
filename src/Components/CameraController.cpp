#include "Object.h"
#include "Game.h"
#include "CameraController.h"
#include <iostream>

using namespace std;

void CameraController::update()
{
	if (player) {
		sf::View nView = win->getView();
		sf::Vector2f playPos = player->getPos();
		sf::Vector2f nPos(clamp(playPos.x, lowerBound.x, upperBound.x), clamp(playPos.y, lowerBound.y, upperBound.y));
		nView.setCenter(nPos);
		win->setView(nView);
	}
}

void CameraController::init() {
	win = object->getGame()->getWindow();
}

void CameraController::setPlayer(Object* nP)
{
	player = nP;
}

void CameraController::setBounds(sf::Vector2f lower, sf::Vector2f upper)
{
	lowerBound = lower;
	upperBound = upper;
}
