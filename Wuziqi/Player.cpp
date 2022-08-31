#include "Player.h"
#include "Chess.h"
#include<iostream>

using std::cout;
using std::endl;

void Player::init(Chess* chess){
	this->chess = chess;
}

void Player::go()
{
	MOUSEMSG msg;  // easyX lib, for getting mouse message
	ChessPos pos;
	
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN
			&& chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	
	printf("%d, %d\n", pos.row, pos.col);
	// put chess piece
	chess->chessDown(&pos, CHESS_BLACK);
}
