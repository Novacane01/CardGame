#include "Card.h"

Card::Card():type(Card::TYPE::NONE),name("None"),rarity(Card::RARITY::NONE),cost(-1),description("NONE") {

}
Card::Card(Card::TYPE type, std::string name, Card::RARITY rarity, int cost, std::string description):type(type),name(name), rarity(rarity),cost(cost),description(description) {
	
}

int Card::getCost() const {
	return cost;
}

Card::RARITY Card::getRarity() const {
	return rarity;
}

Card::TYPE Card::getType() const {
	return type;
}

std::string Card::getName() const {
	return name;
}

std::string Card::getDescription() const {
	return description;
}

void Card::playEffect() {

}

//***************************//
CreatureCard::CreatureCard(std::string name, Card::RARITY rarity, int cost, int attack, int health, std::string description, Card::TYPE type):Card(type,name,rarity,cost, description) {
	this->attack = attack;
	this->health = health;
}

void CreatureCard::setAttack(int attack) {
	this->attack = attack;
}

void CreatureCard::setHealth(int health) {
	this->health = health;
}

int CreatureCard::getAttack() const {
	return attack;
}

int CreatureCard::getHealth() const {
	return health;
}

//*************************//
SpellCard::SpellCard(std::string name, Card::RARITY rarity, int cost, std::string description, Card::TYPE type):Card(type, name, rarity, cost, description) {

}

//**************************//
MagmaWarrior::MagmaWarrior(std::string name, Card::RARITY rarity, int cost, int attack, int health, std::string description) : CreatureCard(name, rarity, cost, attack, health, description) {

}

void MagmaWarrior::playEffect() {
	setAttack(getAttack() + 1);
	setHealth(getHealth() + 1);
}