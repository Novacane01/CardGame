#pragma once
#include "Player.h"

class Battle {
public:
	enum class PHASE{DRAW, MAIN, BATTLE, MAIN2, END };
	Battle(Player *, Player *);
	void Start();
	void Draw(std::vector<Card>*,std::vector<Card>*);
	void nextPhase();
	void switchTurn();
private:
	PHASE phase;
	const int maxHand = 7;
	const int initCardstoDraw = 6;
	int turn = 0;
	int playerTurn[2] = {1,2};
	Player* players[2];
	bool gameIsWon = false;
};

