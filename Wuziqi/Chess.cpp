#include "Chess.h"
#include <math.h>
#include<mmsyscom.h>
#pragma comment(lib, "winmm.lib")

// a function for removing the non-transparent backgroud of chess piece pictures. EasyX itself des not support the transparent background.
void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

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
	mciSendString("play res/start.mp3", 0, 0, 0);
	
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

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	int x = margin_x + chessSize * (pos->col - 0.5);
	int y = margin_y + chessSize * (pos->row - 0.5);

	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}

	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return 0;
}

int Chess::getChessData(int row, int col)
{
	int res = this->chessMap[row][col];
	return res;
}

bool Chess::checkOver()
{
	return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
	chessMap[pos->row][pos->col] =
		playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;  // change the side
}
