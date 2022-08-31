#include "ChessGame.h"

ChessGame::ChessGame(Player* player, AI* ai, Chess* chess) :
	player(player), ai(ai), chess(chess) {

	player->init(chess);

}

void ChessGame::play()
{
	chess->init();
	while (1) {
		player->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

	}
}
