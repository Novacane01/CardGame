#pragma once
#include <vector>
#include "Card.h"

class Player {
public:
	enum class STATE{MAIN, BATTLE}; //Subject to change--might need more/name changes
//*********Player Functions*******//
	Player(std::string);
	void addCardInventory(Card *);
	void removeCardInventory(Card *);
	void addCardDeck(Card *);
	void removeCardDeck(Card *);
	std::vector<Card*>* getDeck();
	std::vector<Card*>* getInventory();
	void setHealth(int);
	int getHealth() const;
	void setEnergy(int);
	int getEnergy() const;
	std::string getName() const;
	STATE state;

//*******Player Battle Components***********//
public:
	std::vector<Card*> hand;
	std::vector<Card*> field;
	std::vector<Card*> tempDeck;
	std::vector<Card*> graveyard;

//********UI*********//
public:
	void updateField(sf::RenderWindow *);
	void updateHand();
	void drawHand(sf::RenderWindow *);
	void displayUI(sf::RenderWindow *);
	void setUI();
	
	sf::Text healthUI;
	sf::Text energyUI;
	sf::CircleShape playerHUD;

	
private:
	std::vector<Card*> inventory;
	const int deckSize = 40;
	std::vector<Card*> deck;
	int health = 20;
	int energy = 0;
	const std::string name;
	bool priority;
};
