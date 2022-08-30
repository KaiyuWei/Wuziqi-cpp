#pragma once
#include<graphics.h>  // easyX graphics library
#include<vector>

using std::vector;

struct ChessPos {
	/*
	* The position of chess pieces
	*/
	int row;
	int col;
}; 

typedef enum { 
	/*
		type of pieces, white or black
	*/
	CHESS_WHITE = -1,
	CHESS_BLACK = 1,
} chess_kind_t;


class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);  // constructor
	void init();
	bool clickBoard(int x, int y, ChessPos * pos);
	void chessDown(ChessPos* row, chess_kind_t);
	int getGradeSize();  // gain the size of the board
	bool checkOver();  // check if the game is over
private:
	IMAGE chessBlackImg;  // black piece
	IMAGE chessWhiteImg;  // white piece
	int gradeSize;
	int margin_x;  // left margin of the board
	int margin_y;  // top margin of the board
	float chessSize;  // size of the piece
	vector<vector<int>> chessMap;  // store the current board status
	bool playerFlag;  // which player's turn. True: black, False: white

};

