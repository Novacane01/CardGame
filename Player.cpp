#include "Player.h"

Player::Player(std::string name):name(name) {

}

std::string Player::getName() const {
	return name;
}

void Player::addCardDeck(Card *card) {
	deck.push_back(*card);
}

void Player::removeCardDeck(Card *card) {
	for (std::vector<Card>::iterator p = deck.begin();p != deck.end();p++) {
		if (p->getName() == card->getName()) {
			deck.erase(p);
			break;
		}
	}
}

void Player::removeCardInventory(Card *card) {
	for (std::vector<Card>::iterator p = inventory.begin();p != inventory.end();p++) {
		if (p->getName() == card->getName()) {
			inventory.erase(p);
			break;
		}
	}
}

void Player::addCardInventory(Card *card) {
	inventory.push_back(*card);
}

 std::vector<Card>* Player::getDeck(){
	return &deck;
}

 std::vector<Card>* Player::getInventory() {
	 return &inventory;
 }

 void Player::setHealth(int health) {
	 this->health = health;
 }

 void Player::setEnergy(int energy) {
	 this->energy = energy;
 }

 int Player::getHealth() const {
	 return health;
 }

 int Player::getEnergy() const {
	 return energy;
 }
