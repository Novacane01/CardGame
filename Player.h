#pragma once
#include <vector>
#include "Card.h"

class Player {
public:
	Player(std::string);
	void addCardInventory(Card *);
	void removeCardInventory(Card *);
	void addCardDeck(Card *);
	void removeCardDeck(Card *);
	std::vector<Card>* getDeck();
	std::vector<Card>* getInventory();
	void setHealth(int);
	int getHealth() const;
	void setEnergy(int);
	int getEnergy() const;
	std::string getName() const;

private:
	std::vector<Card> inventory;
	const int deckSize = 40;
	std::vector<Card> deck;
	int health;
	int energy;
	const std::string name;
};
