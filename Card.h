#pragma once
#include <string>
#include "SFML\Graphics.hpp"

class Card {

public:
	Card & operator=(const Card &x) {
		return *this;
	}
	Card();
	const enum class RARITY { NONE, UNCOMMON, COMMON, RARE, LEGENDARY };
	const enum class TYPE { NONE, CREATURE, SPELL };
	Card(Card::TYPE, std::string, Card::RARITY, int, std::string);
	int getCost() const;
	Card::RARITY getRarity() const;
	Card::TYPE getType() const;
	std::string getName() const;
	std::string getDescription() const;
	virtual void playEffect();
	//~Card();

private:
	const RARITY rarity;
	const TYPE type;
	const int cost;
	const std::string name;
	const std::string description;
	
};

class CreatureCard:public Card {
public:
	CreatureCard(std::string,Card::RARITY,int, int, int, std::string, Card::TYPE = Card::TYPE::CREATURE);
	void setAttack(int);
	void setHealth(int);
	int getAttack() const;
	int getHealth() const;
private:
	int attack;
	int health;
};

class SpellCard :public Card {
public:
	SpellCard(std::string, Card::RARITY, int, std::string, Card::TYPE = Card::TYPE::SPELL);
private:

};

class MagmaWarrior : public CreatureCard {
public:
	MagmaWarrior(std::string name = "Magma Warrior",
	Card::RARITY rarity = Card::RARITY::RARE,
	int cost = 3,
	int attack = 4,
	int health = 4,
	std::string description = "When Magma Warrior enteres the battlefield add a +1/+1 to it.");
	void playEffect();
private:

};