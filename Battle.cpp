#include "Battle.h"

Battle::Battle(Player *player1, Player *player2):player1(player1),player2(player2) {
	LOG("Starting Game...");
	/*std::thread first(player1->updateField);
	first.detach();
	std::thread second(player2->updateField);
	second.detach();*/

	if ((float)rand() / RAND_MAX < .5f) {
		currentPlayer = player1;
		opposingPlayer = player2;
		LOG("Player 1 goes first.");
	}
	else {
		currentPlayer = player2;
		opposingPlayer = player1;
		LOG("Player 2 goes first.");
	}
}

void Battle::Start() {
	
	player1->tempDeck = *player1->getDeck();
	player2->tempDeck = *player2->getDeck();
	LOG("Decks initialized.");

	//***Initial Draw Phase***//
	LOG("Switching to Initial Draw Phase...");
	phase = PHASE::DRAW;


	for (int i = 0;i < initCardstoDraw;i++) {
		Draw(player1);
		Draw(player2);
	}
	LOG("Cards added to hand.");

	//***Incrementing Phase***//
	LOG("Switching to Main Phase...");
	nextPhase();

	//***Battle Loop***//
	while (!gameIsWon) {

		LOG("Turn: " + std::to_string(++turn));

		currentPlayer->setEnergy(ceil((float)turn / 2));

		if (phase == PHASE::DRAW) {
			LOG("Drawing Card...");
			Draw(currentPlayer);
			nextPhase();
		}
		if (phase == PHASE::MAIN) {
			LOG("MAIN PAHSE");
			LOG("Energy:" + std::to_string(currentPlayer->getEnergy()));
			while (phase == PHASE::MAIN) {
				LOG("1. Play Card\n2. Battle\n3. End Turn");
				int option;
				std::cin >> option;
				switch (option) {
				case 1:
					displayCards(currentPlayer);
					break;
				case 2:
					if (currentPlayer->field.size() > 0) {
						initBattle();
					}
					else {
						LOG("You have no creatures to attack with!");
					}
					break;
				case 3:
					phase = PHASE::END;
					break;
				}
			}
		}
		if (phase == PHASE::BATTLE) {

		}
		if (phase == PHASE::END) {
			switchTurn();
			nextPhase();
		}
	}
}

void Battle::Draw(Player *player) {
	if (player->tempDeck.size() > 0) {
		player->hand.push_back(player->tempDeck.back());
		player->tempDeck.erase(player->tempDeck.end() - 1);
	}
	else {
		gameIsWon = true;
	}
}

void Battle::nextPhase() {
	int phaseNum = static_cast<int>(phase);
	if (phaseNum < 4) {
		phaseNum++;
	}
	else {
		phaseNum = 0;
	}
	phase = static_cast<PHASE>(phaseNum);
}

void Battle::playCard(Player *player, Card &card, int pos) {
	if (card.getType() == Card::TYPE::CREATURE) {
		player->field.push_back(&card);
		player->hand.erase(player->hand.begin() + pos);
		LOG(player->getName() + " has summoned " + card.getName() + " to the field!");
		if (card.getEffect() == Card::EFFECT::OFE) {
			LOG(card.getName() + "Triggered its special ability!");
			card.playEffect();
		}
	}
	else if(card.getType() == Card::TYPE::SPELL){
		card.playEffect();
		LOG(player->getName() + " played " + card.getName());
	}
}

void Battle::switchTurn() {
	if (currentPlayer == player1) {
		LOG("Player 2's turn");
		currentPlayer = player2;
	}
	else if (currentPlayer == player2) {
		LOG("Player 1's turn");
		currentPlayer = player1;
	}
}

void Battle::displayCards(Player *player) {
	for (unsigned i = 0;i < player->hand.size();i++) {
		LOG(std::to_string(i + 1) + ". " + player->hand[i]->getName());
	}
	LOG("-1. Cancel");
	while (true) {
		int option;
		std::cin >> option;
		if (option > 0 && option < player->hand.size()) {
			Card *cardChoice = player->hand[option - 1];
			if (player->getEnergy() >= cardChoice->getCost()) {
				playCard(player, *cardChoice, option - 1);
				player->setEnergy(player->getEnergy() - cardChoice->getCost());
			}
			else {
				LOG("You don't have enough energy to play this card!")
			}
		}
		else if (option == -1) {
			return;
		}
	}
}

void Battle::displayField(Player *player) {
	LOG("FIELD:");
	LOG("Player 1: ");
	for (unsigned i = 0;i < currentPlayer->field.size();i++) {
		if (CreatureCard *card = dynamic_cast<CreatureCard*>(currentPlayer->field[i])) {
			LOG(std::to_string(i + 1) +". " + card->getName() + " " +  std::to_string(card->getAttack()) + "/" + std::to_string(card->getHealth()));
		}
	}
	LOG("Select a monster to attack with.");
	int option;
	std::cin >> option;
	Card *temp = currentPlayer->field[option - 1];
	LOG("Player 2: ");
	if (player2->field.size() > 0) {
		for (unsigned i = 0;i < opposingPlayer->field.size();i++) {
			if (CreatureCard *card = dynamic_cast<CreatureCard*>(opposingPlayer->field[i])) {
				LOG(std::to_string(i + 1) + card->getName());
			}
		}
		LOG("Select a target.");
		std::cin >> option;
		Card *tempTarget = opposingPlayer->field[option - 1];
	}
	else {

	}
}

void Battle::initBattle() {
	displayField(currentPlayer);
}