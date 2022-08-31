#include "Player.h"
#include "Chess.h"

void Player::init(Chess* chess){
	this->chess = chess;
}

void Player::go()
{
	MOUSEMSG msg;  // easyX lib, for getting mouse message
	ChessPos pos;

	// get mouse information
	msg = GetMouseMsg();

	while (1) {
		// determine if it is an effective location
		if (msg.uMsg == WM_LBUTTONDOWN
			&& chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	
	chess->chessDown(&pos, CHESS_BLACK);
}
