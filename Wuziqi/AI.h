#pragma once
#include "Chess.h"
#include<vector> 

using std::vector;

class AI
{
public:
	void init(Chess *chess);
	void go();
private:
	Chess* chess;
	vector<vector<int>> scoreMap;  // scoring data

private:
	void calculateScore();
};

