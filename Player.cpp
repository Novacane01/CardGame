#include "Player.h"

Player::Player(std::string name):name(name) {
}

std::string Player::getName() const {
	return name;
}

void Player::addCardDeck(Card *card) {
	deck.push_back(card);
}

void Player::removeCardDeck(Card *card) {
	for (std::vector<Card*>::iterator p = deck.begin();p != deck.end();p++) {
		if ((*p)->getName() == card->getName()) {
			deck.erase(p);
			break;
		}
	}
}

void Player::removeCardInventory(Card *card) {
	for (std::vector<Card*>::iterator p = inventory.begin();p != inventory.end();p++) {
		if ((*p)->getName() == card->getName()) {
			inventory.erase(p);
			break;
		}
	}
}

void Player::addCardInventory(Card *card) {
	inventory.push_back(card);
}

 std::vector<Card*>* Player::getDeck(){
	return &deck;
}

 std::vector<Card*>* Player::getInventory() {
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

 void Player::updateHand() {
	 for (int i = 0;i < hand.size();i++) {
		 if (i == 0) {
			 hand[i]->getCard()->setPosition(WINDOW_WIDTH / 2 - hand.size()*hand[i]->getCard()->getSize().x / 4, WINDOW_HEIGHT * 0.95f);
		 }
		 else {
			 hand[i]->getCard()->setPosition(hand[i - 1]->getCard()->getPosition().x + hand[i]->getCard()->getSize().x / 2, hand[i - 1]->getCard()->getPosition().y);
		 }
	 }
 }

 void Player::updateField(sf::RenderWindow *window) {
	 for (Card *c : field) {
		 window->draw(*c->getCard());
	 }
 }

 void Player::drawHand(sf::RenderWindow *window) {
	 for (Card *c : hand) {
		 window->draw(*c->getCard());
	 }
 }

 void Player::setUI() {
	 if (state == Player::STATE::BATTLE) {
		 playerHUD.setRadius(200.f);
		 playerHUD.setPosition(sf::Vector2f(WINDOW_WIDTH - playerHUD.getRadius(), WINDOW_HEIGHT - playerHUD.getRadius()));
		 healthUI.setPosition(sf::Vector2f(playerHUD.getPosition().x - 50, playerHUD.getPosition().y - 25));
		 healthUI.setFont(GameManager::font);
		 healthUI.setCharacterSize(50);
		 healthUI.setOutlineThickness(2.f);
	 }
 }

 void Player::displayUI(sf::RenderWindow *window) {
	 if (state == Player::STATE::BATTLE) {
		 healthUI.setString(std::to_string(health));
		 window->draw(playerHUD);
		 window->draw(healthUI);
	 }
 }