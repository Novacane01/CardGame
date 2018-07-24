#pragma once
#include <string>
#include "GameManager.h"


class Card {

public:
	Card & operator=(const Card &x) {
		return *this;
	}
	Card();
	enum class RARITY { NONE, UNCOMMON, COMMON, RARE, LEGENDARY };
	enum class TYPE { NONE, CREATURE, SPELL };
	enum class EFFECT { NONE, OFE, GAINLIFE, STATBOOST, DRAW, DISCARD, SHUFFLE };
	Card(Card::TYPE, std::string, Card::RARITY, int, std::string, Card::EFFECT);
	int getCost() const;
	Card::RARITY getRarity() const;
	Card::TYPE getType() const;
	std::string getName() const;
	std::string getDescription() const;
	Card::EFFECT getEffect() const;
	sf::RectangleShape* getCard();
	virtual void playEffect();
	virtual void Update(sf::RenderWindow &, float);
	void Draw(sf::RenderWindow &);
	void setCardInfo(); 
	static void viewCard(sf::RenderWindow *, Card *card = 0);
	static sf::RectangleShape cardInfoDisplay;
	bool viewing;
	//~Card();

private:
	const RARITY rarity;
	const TYPE type;
	const EFFECT effect;
	const int cost;
	const std::string name;
	const std::string description;

	sf::RectangleShape card = sf::RectangleShape(sf::Vector2f(125, 200));
	/*sf::Sprite cardArt;
	sf::Texture texture;*/
	sf::Text cardInfo;
};


class CreatureCard:public Card {
public:
	CreatureCard(std::string,Card::RARITY,int, int, int, std::string, Card::EFFECT, Card::TYPE = Card::TYPE::CREATURE);
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
	SpellCard(std::string, Card::RARITY, int, std::string, Card::EFFECT, Card::TYPE = Card::TYPE::SPELL);
private:

};

class MagmaWarrior : public CreatureCard {
public:
	MagmaWarrior(std::string name = "Magma Warrior",
	Card::RARITY rarity = Card::RARITY::RARE,
	int cost = 3,
	int attack = 4,
	int health = 4,
	std::string description = "When Magma Warrior enters the battlefield add a +1/+1 counter to it.",
	EFFECT effect = Card::EFFECT::OFE);
	void playEffect();
private:

};