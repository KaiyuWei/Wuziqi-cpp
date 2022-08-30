#include "Chess.h"


Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize):
	gradeSize(gradeSize), margin_x(marginX), margin_y(marginY), chessSize(chessSize)
{
	this->playerFlag = CHESS_BLACK;
	for (int i = 0; i < chessMap.size(); i++) {
		vector<int> row;
		for (int j = 0; j < chessMap.size(); j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
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
