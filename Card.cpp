#include "Card.h"
#include "Effects.h"

sf::RectangleShape Card::cardInfoDisplay = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH / 4, WINDOW_HEIGHT));

//Default Constructor
Card::Card():type(Card::TYPE::NONE),name("None"),rarity(Card::RARITY::NONE),cost(-1),description("NONE"),effect(EFFECT::NONE) {

}

//Non-Default Constructor 
Card::Card(Card::TYPE type, std::string name, Card::RARITY rarity, int cost, std::string description, Card::EFFECT effect):type(type),name(name), rarity(rarity),cost(cost),description(description),effect(effect) {
	card.setSize(sf::Vector2f(125,200));
	card.setOutlineColor(sf::Color::Black);
	card.setOutlineThickness(1);
	card.setOrigin(card.getSize().x / 2, card.getSize().y/2);
	card.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	cardInfoDisplay.setFillColor(sf::Color(169,169,169,50));
	text.setString(description);
	text.setCharacterSize(15);
	text.setFont(GameManager::font);
	text.setPosition(0, cardInfoDisplay.getSize().y / 2);
}

//Returns card cost
int Card::getCost() const {
	return cost;
}

//Returns card rarity
Card::RARITY Card::getRarity() const {
	return rarity;
}

//Returns card type
Card::TYPE Card::getType() const {
	return type;
}

//Returns card name
std::string Card::getName() const {
	return name;
}

//Returns card description
std::string Card::getDescription() const {
	return description;
}


void Card::playEffect() {

}

sf::RectangleShape* Card::getCard() {
	return &card;
}

//Updates card UI
void Card::Update(sf::RenderWindow &window, float dt) {
	Draw(window);
}

//Draws card to window
void Card::Draw(sf::RenderWindow &window) {
	window.draw(card);
}

//Returns card effect type
Card::EFFECT Card::getEffect() const {
	return effect;
}

void Card::displayCardInfo(sf::RenderWindow *window, Card *card) {
	window->draw(card->text);
}

void Card::updateCardInfo(sf::RenderWindow *window, Card *card) {
	if (card) {
		window->draw(cardInfoDisplay);
		window->draw(card->text);
	}
}

//***********Creature Card Functions****************//

//Default Constructor
CreatureCard::CreatureCard(std::string name, Card::RARITY rarity, int cost, int attack, int health, std::string description, Card::EFFECT effect, Card::TYPE type):Card(type,name,rarity,cost, description, effect) {
	this->attack = attack;
	this->health = health;
}

//Sets creature's attack
void CreatureCard::setAttack(int attack) {
	this->attack = attack;
}

//Sets creature's health
void CreatureCard::setHealth(int health) {
	this->health = health;
}

//Returns creature's attack
int CreatureCard::getAttack() const {
	return attack;
}

//Returns creature's health
int CreatureCard::getHealth() const {
	return health;
}

//***********Spell Card Functions**************//

//Default Constructor
SpellCard::SpellCard(std::string name, Card::RARITY rarity, int cost, std::string description, Card::EFFECT effect, Card::TYPE type):Card(type, name, rarity, cost, description, effect) {

}

//************Creature Effects**************//
MagmaWarrior::MagmaWarrior(std::string name, Card::RARITY rarity, int cost, int attack, int health, std::string description, Card::EFFECT effect) : CreatureCard(name, rarity, cost, attack, health, description, effect) {

}

void MagmaWarrior::playEffect() {
	Effects::boostStats(this, 1, 1);
}