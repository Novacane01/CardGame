#pragma once
#include "GameManager.h"
#include "Player.h"
#include <map>
#include <iostream>

class Battle {
public:
	enum class PHASE{DRAW, MAIN, BATTLE, MAIN2, END };
	Battle(Player *, Player *);
	void Start(sf::RenderWindow *);
	void Draw(Player *);
	void nextPhase();
	void playCard(Player *, Card *, int);
	void switchTurn();
	void displayCards(Player *);
	void displayField(Player *);
	void updateLog(sf::RenderWindow *);
	void initBattle();
	static void Update(float, Player *);
	void Log(std::string);
private:
	PHASE phase;
	const int maxHand = 7;
	const int initCardstoDraw = 6;
	int turn = 0;
	Player * const player1;
	Player * const player2;
	Player * currentPlayer;
	Player * opposingPlayer;
	bool gameIsWon = false;
	sf::Text battleLog;
	sf::RectangleShape battleLogBox = sf::RectangleShape(sf::Vector2f(200, 200));
	std::string log;
};

