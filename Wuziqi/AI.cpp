#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);  // pretend to think XD
	chess->chessDown(&pos, CHESS_WHITE);
}

void AI::calculateScore()
{
	int personNum = 0;  // how many consecutive pieces the player(black) has in one direction
	int aiNum = 0;  // how many consecutive pieces the ai(white) has in one direction
	int emptyNum = 0;  // available nodes in one direction
	
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap.size(); j++) {
			scoreMap[i][j] = 0;  // clear the scoreMap
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			
			// score for all available nodes
			if (chess->getChessData(row, col)) continue;  // if there is a piece, skip

			// all possible directions (in total: 4) of a node should be considered when scoring
			// x, y are variables for controlling the directions
			for (int y = -1; y <= 0; y++) {
				for (int x = -1; x <= 1; x++) {
					if (y == 0 && x == 0) continue; 
					if (y == 0 && x != 1) continue;

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// if black is at current node
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							// if legal position and has black piece
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;  // empty node terminate the inner for loop
						}
						else break;
					}
					// calculate in reverse direction
					for (int i = 1; i < 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							// if legal position and has black piece
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;  // empty node terminate the inner for loop
						}
						else break;
					}

					if (personNum == 1) {  // consecutive 2 pieces
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {  // consecutive 3 pieces
						if (emptyNum == 1) { // dead consecutive 3
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {  // sustained consecutive 3
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {  // consecutive 4
						if (emptyNum == 1) {  // dead consec 4
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2) {  // sustained consec 4
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4) {  // consec 5, will win
						scoreMap[row][col] += 20000;
					}

					// if white(ai) is at current node
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							// if current position has white piece
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;  // empty node terminate the inner for loop
						}
						else break;
					}
					// inverse direction
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							// if current position has white piece
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;  // empty node terminate the inner for loop
						}
						else break;
					}

					if (aiNum == 0) {
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {  // consecutive 2 pieces
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {  // consecutive 3 pieces
						if (emptyNum == 1) { // dead consecutive 3
							scoreMap[row][col] += 25;
						}
						if (emptyNum == 2) {  // sustained consecutive 3
							scoreMap[row][col] += 50;
						}
					}
					else if (aiNum == 3) {  // consecutive 4
						if (emptyNum == 1) {  // dead consec 4
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2) {  // sustained consec 4
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum == 4) {
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}

}

ChessPos AI::think()
{
	calculateScore();

	int maxScore = 0;
	vector<ChessPos> maxPoints;  // if more than one nodes have max score, randomly chooose one
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (!chess->getChessData(row, col)) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxPoints.push_back(ChessPos(row, col));
				}	
			}
		}
	}
	int index = rand() % maxPoints.size();

	return maxPoints[index];
}
