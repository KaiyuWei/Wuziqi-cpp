#include <iostream>
#include "ChessGame.h"

int main() {
	Player player;
	Chess chess(13, 44, 43, 67.3);  // the input arguments are from the picture resource of the board
	AI ai;
	ChessGame game(&player, &ai, &chess);

	game.play();

	return 0;
}