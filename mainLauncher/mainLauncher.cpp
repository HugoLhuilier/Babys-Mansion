#include <SFML/Graphics.hpp>

#include "Game.h"

int main(int argc, char** argv) {
	Game game(sf::VideoMode::getFullscreenModes()[0]);
	game.startGame();

	return 0;
}