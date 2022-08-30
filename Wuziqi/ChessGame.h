#pragma once
#include "Player.h"
#include "AI.h"
#include "Chess.h"

class ChessGame
{
public:
	ChessGame(Player* player, AI* ai, Chess* chess);
	void play();  // start the game

private:
	Player* player;
	AI* ai;
	Chess* chess;
};

