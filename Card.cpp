#include "Card.h"
#include "Effects.h"

Card::Card():type(Card::TYPE::NONE),name("None"),rarity(Card::RARITY::NONE),cost(-1),description("NONE"),effect(EFFECT::NONE) {
	
}
Card::Card(Card::TYPE type, std::string name, Card::RARITY rarity, int cost, std::string description, Card::EFFECT effect):type(type),name(name), rarity(rarity),cost(cost),description(description),effect(effect) {
	card.setSize(sf::Vector2f(125,200));
	card.setOrigin(card.getSize().x / 2, card.getSize().y/2);
	card.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
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

void Card::Update(sf::RenderWindow &window, float dt) {
	Draw(window);
}

void Card::Draw(sf::RenderWindow &window) {
	window.draw(card);
}

Card::EFFECT Card::getEffect() const {
	return effect;
}

//***************************//
CreatureCard::CreatureCard(std::string name, Card::RARITY rarity, int cost, int attack, int health, std::string description, Card::EFFECT effect, Card::TYPE type):Card(type,name,rarity,cost, description, effect) {
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
SpellCard::SpellCard(std::string name, Card::RARITY rarity, int cost, std::string description, Card::EFFECT effect, Card::TYPE type):Card(type, name, rarity, cost, description, effect) {

}

//**************************//
MagmaWarrior::MagmaWarrior(std::string name, Card::RARITY rarity, int cost, int attack, int health, std::string description, Card::EFFECT effect) : CreatureCard(name, rarity, cost, attack, health, description, effect) {

}

void MagmaWarrior::playEffect() {
	Effects::boostStats(this, 1, 1);
}