#include "Effects.h"

void Effects::drawCard(Player *player) {
	if (player->tempDeck.size() > 0) {
		player->hand.push_back(player->tempDeck.back());
		player->tempDeck.erase(player->tempDeck.end() - 1);
	}
}

void Effects::gainLife(Player *player, int life) {
	player->setHealth(player->getHealth() + life);
}

void Effects::boostStats(CreatureCard *card, int attack, int health) {
	card->setAttack(card->getAttack() + attack);
	card->setHealth(card->getHealth() + health);
}

void Effects::discardCard(Player *player, Card *card) {
	for (std::vector<Card *>::iterator it; it != player->hand.end();it++) {
		if ((*it) == card) {
			player->graveyard.push_back(card);
			player->hand.erase(it);
			break;
		}
	}
}