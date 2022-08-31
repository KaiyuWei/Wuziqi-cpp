#include "Chess.h"
#include<mmsyscom.h>
#pragma comment(lib, "winmm.lib")

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize) :
	gradeSize(gradeSize), margin_x(marginX), margin_y(marginY), chessSize(chessSize)
{
	this->playerFlag = CHESS_BLACK;
	for (int i = 0; i < gradeSize; i++) {
		vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	// create game window by easyX function
	initgraph(897, 895);  // the arguments depend on the size of the board picture

	// show the board picture
	loadimage(0, "res/board2.jpg");
	// play the starting music
	mciSendString("play res/start.wav", 0, 0, 0);
	
	// load piece pictures
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessBlackImg, "res/white.png", chessSize, chessSize, true);

	// clear the chessboard
	for (int i = 0; i < chessMap.size(); i++) {
		for (int j = 0; j < chessMap.size(); j++) {
			chessMap[i][j] = 0;
		}
	}

	playerFlag = true;  // black goes the first
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	return false;
}

void Chess::chessDown(ChessPos* row, chess_kind_t)
{
}

int Chess::getGradeSize()
{
	return 0;
}

bool Chess::checkOver()
{
	return false;
}
