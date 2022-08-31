#include "Chess.h"
#include <math.h>
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
	initgraph(897, 895, EW_SHOWCONSOLE);  // the arguments depend on the size of the board picture

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

bool Chess::clickBoard(int x, int y, ChessPos* pos) {
	int col = (x - margin_x) / chessSize;  
	int row = (y - margin_y) / chessSize;
	int offset = chessSize * 0.4;  // the error tolerance 
	int len;  // the distance between the selected position and the chessboard effective points.

	// left top
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	len = sqrt((x - leftTopPosX) * (x - leftTopPosX) +
		(y - leftTopPosY) * (y - leftTopPosY));
	if (len < offset) {
		pos->row = row;
		pos->col = col;

		if (!chessMap[pos->row][pos->col]) {
			return true;  // if no piece in the selected position
		}
	}

	// right top	
	int rightTopPosX = leftTopPosX + chessSize;
	int rightTopPosY = leftTopPosY;
	len = sqrt((x - rightTopPosX) * (x - rightTopPosX) +
		(y - rightTopPosY) * (y - rightTopPosY));
	if (len < offset) {
		pos->row = row;
		pos->col = col + 1;

		if (!chessMap[pos->row][pos->col]) {
			return true;  // if no piece in the selected position
		}
	}

	// left bottom
	int leftBottomPosX = leftTopPosX;
	int leftBottomPosY = leftTopPosY + chessSize;
	len = sqrt((x - leftBottomPosX) * (x - leftBottomPosX) +
		(y - leftBottomPosY) * (y - leftBottomPosY));
	if (len < offset) {
		pos->row = row + 1;
		pos->col = col;

		if (!chessMap[pos->row][pos->col]) {
			return true;  // if no piece in the selected position
		}
	}

	// right bottom
	int rightBottomPosX = leftTopPosX + chessSize;
	int rightBottomPosY = leftTopPosY + chessSize;
	len = sqrt((x - rightBottomPosX) * (x - rightBottomPosX) +
		(y - rightBottomPosY) * (y - rightBottomPosY));
	if (len < offset) {
		pos->row = row + 1;
		pos->col = col + 1;

		if (!chessMap[pos->row][pos->col]) {
			return true;  // if no piece in the selected position
		}
	}
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
