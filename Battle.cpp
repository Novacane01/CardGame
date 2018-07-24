#include "Battle.h"

//Constructor
Battle::Battle(Player *player1, Player *player2):player1(player1),player2(player2) {

	setUI();

	Log("Starting Game...");

	if ((float)rand() / RAND_MAX < .5f) {
		currentPlayer = player1;
		opposingPlayer = player2;
		Log("Player 1 goes first.");
	}
	else {
		currentPlayer = player2;
		opposingPlayer = player1;
		Log("Player 2 goes first.");

	}
	player1->state = Player::STATE::BATTLE;
	player2->state = Player::STATE::BATTLE;
	player1->setUI();
	player2->setUI();
}

//Logs text to battle log
void Battle::Log(std::string string) {
	std::string tempString = "";
	std::string tempChars;
	for (int i = 0, j = 0; j < string.size();i++, j++) {
		tempChars += string[j];
		if (string[j] == ' '||j+1==string.size()) {
			tempString += tempChars;
			battleLog.setString(tempString);
			if (battleLog.findCharacterPos(i).x >= battleLogBox.getPosition().x + battleLogBox.getSize().x - 50) {
				tempString = tempString.substr(0, tempString.size() - tempChars.size());
				tempString += "\n\n";
				//battleLog.move(sf::Vector2f(0, -10));
				battleLog.setString(tempString);
				tempString += tempChars;
				i += 2;
			}
			tempChars.clear();
		}
	}
	log += tempString + "\n\n";
	battleLog.move(sf::Vector2f(0, -30));
}

//Initiates the battle
void Battle::Start(sf::RenderWindow *window) {
	std::thread(&Battle::initBattle,this).detach();
	Card * highlightedCard = nullptr;
	int highlightedCardPos = -1;
	while (window->isOpen()) {
		sf::sleep(sf::seconds(0.1f));
		window->clear();
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::MouseMoved) {
				for (int i = 0; i < currentPlayer->hand.size();i++) {
					if (currentPlayer->hand[i]->getCard()->getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)))) {
						currentPlayer->hand[i]->getCard()->setPosition(sf::Vector2f(currentPlayer->hand[i]->getCard()->getPosition().x,WINDOW_HEIGHT*0.95f-50));
						currentPlayer->hand[i]->viewing = true;
						highlightedCard = currentPlayer->hand[i];
						highlightedCardPos = i;
						if (i > 0) {
							currentPlayer->hand[i-1]->getCard()->setPosition(sf::Vector2f(currentPlayer->hand[i-1]->getCard()->getPosition().x, WINDOW_HEIGHT*0.95f));
						}
						if (i < currentPlayer->hand.size()-1) {
							currentPlayer->hand[i+1]->getCard()->setPosition(sf::Vector2f(currentPlayer->hand[i+1]->getCard()->getPosition().x, WINDOW_HEIGHT*0.95f));
						}
					}
					else if (currentPlayer->hand[i]->viewing) {
						currentPlayer->hand[i]->getCard()->setPosition(sf::Vector2f(currentPlayer->hand[i]->getCard()->getPosition().x, WINDOW_HEIGHT*0.95f));
						highlightedCard = (highlightedCard == currentPlayer->hand[i])? 0:highlightedCard;
						highlightedCardPos = (highlightedCard) ? highlightedCardPos : -1;
					}
				}
				for (int i = 0; i < currentPlayer->field.size();i++) {
					if (currentPlayer->field[i]->getCard()->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
						highlightedCard = currentPlayer->field[i];
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (highlightedCard&&highlightedCardPos!=-1&&phase==PHASE::MAIN) {
						if (currentPlayer->getEnergy() >= highlightedCard->getCost()) {
							playCard(currentPlayer, highlightedCard, highlightedCardPos);
						}
					}
					if (endTurnButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
						phase = PHASE::END;
					}
				}
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					if (battleLogBox.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
						battleLog.move((signbit(event.mouseWheelScroll.delta) && battleLogBox.getPosition().y <= battleLog.getPosition().y) ? sf::Vector2f(0, 0): sf::Vector2f(0, -event.mouseWheelScroll.delta * 10));
					}
				}
			}
		}
		Card::viewCard(window, highlightedCard);
		displayUI(window);
		window->display();
	}
}

//Draws a card from deck
bool Battle::Draw(Player *player) {
	if (player->tempDeck.size() > 0) {
		player->hand.push_back(player->tempDeck.back());
		player->tempDeck.erase(player->tempDeck.end() - 1);
		player->updateHand();
		return true;
	}
	else {
		gameIsWon = true;
	}
	return false;
}

//Increments Phase
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

//Puts card on the field
void Battle::playCard(Player *player, Card *card, int pos) {
	if (card->getType() == Card::TYPE::CREATURE) {
		player->field.push_back(card);
		player->hand.erase(player->hand.begin() + pos);
		Log(player->getName() + " has summoned " + card->getName() + " to the field!");
		if (card->getEffect() == Card::EFFECT::OFE) {
			Log(card->getName() + " triggered its special ability!");
			card->playEffect();
		}
	}
	else if(card->getType() == Card::TYPE::SPELL){
		card->playEffect();
		Log(player->getName() + " played " + card->getName());
	}
	player->setEnergy(player->getEnergy() - card->getCost());
	currentPlayer->updateHand();
}

//Switches current player
void Battle::switchTurn() {
	if (currentPlayer == player1) {
		Log("Player 2's turn");
		currentPlayer = player2;
	}
	else if (currentPlayer == player2) {
		Log("Player 1's turn");
		currentPlayer = player1;
	}
}

//Displays cards in current
void Battle::displayCards(Player *player) {
	for (unsigned i = 0;i < player->hand.size();i++) {
		Log(std::to_string(i + 1) + ". " + player->hand[i]->getName());
	}
	Log("-1. Cancel");
	while (true) {
		int option;
		std::cin >> option;
		if (option > 0 && option < player->hand.size()) {
			Card *cardChoice = player->hand[option - 1];
			if (player->getEnergy() >= cardChoice->getCost()) {
				playCard(player, cardChoice, option - 1);
				player->setEnergy(player->getEnergy() - cardChoice->getCost());
			}
			else {
				Log("You don't have enough energy to play this card!");
			}
		}
		else if (option == -1) {
			return;
		}
	}
}

//Displays Field
void Battle::displayField(Player *player) {
	Log("FIELD:");
	Log("Player 1: ");
	for (unsigned i = 0;i < currentPlayer->field.size();i++) {
		if (CreatureCard *card = dynamic_cast<CreatureCard*>(currentPlayer->field[i])) {
			Log(std::to_string(i + 1) +". " + card->getName() + " " +  std::to_string(card->getAttack()) + "/" + std::to_string(card->getHealth()));
		}
	}
	Log("Select a monster to attack with.");
	int option;
	std::cin >> option;
	Card *temp = currentPlayer->field[option - 1];
	Log("Player 2: ");
	if (player2->field.size() > 0) {
		for (unsigned i = 0;i < opposingPlayer->field.size();i++) {
			if (CreatureCard *card = dynamic_cast<CreatureCard*>(opposingPlayer->field[i])) {
				Log(std::to_string(i + 1) + card->getName());
			}
		}
		Log("Select a target.");
		std::cin >> option;
		Card *tempTarget = opposingPlayer->field[option - 1];
	}
	else {

	}
}

//Updates battle log
void Battle::updateLog(sf::RenderWindow *window) {
	battleLog.setString(log);
	window->draw(battleLog);
}

void Battle::initBattle() {
	player1->tempDeck = *player1->getDeck();
	player2->tempDeck = *player2->getDeck();
	Log("Decks initialized.");

	//***Initial Draw Phase***//
	Log("Switching to initial draw phase...");
	phase = PHASE::DRAW;


	for (int i = 0;i < initCardstoDraw;i++) {
		Draw(player1);
		Draw(player2);
	}
	Log("Cards added to hand.");

	//***Incrementing Phase***//
	Log("Switching to main phase...");
	nextPhase();

	//***Battle Loop***//
	while (!gameIsWon) {

		Log("Turn: " + std::to_string(++turn));

		currentPlayer->setEnergy(ceil((float)turn / 2));

		if (phase == PHASE::DRAW) {
			Log("Drawing card...");
			if (Draw(currentPlayer)) {
				nextPhase();
			}
			else {
				Log(opposingPlayer->getName() + " has won due to deck out!");
			}
		}
		if (phase == PHASE::MAIN) {
			Log("MAIN PAHSE");
			//Log("Energy:" + std::to_string(currentPlayer->getEnergy()));
			while (phase == PHASE::MAIN) {
				sf::sleep(sf::seconds(.5f));
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

//static void Update(sf::RenderWindow *window, float dt, Player *player) {
//	window->clear();
//	for (Card *c : player->hand) {
//		window->draw(*c->getCard());
//	}
//	window->display();
//}

//Sets UI for battle
void Battle::setUI() {
	battleLogBox.setPosition(WINDOW_WIDTH - battleLogBox.getSize().x, 20);
	//battleLogBox.setFillColor(sf::Color::Red);
	battleLog.setFont(GameManager::font);
	battleLog.setCharacterSize(15);
	battleLog.setPosition(sf::Vector2f(battleLogBox.getPosition().x, battleLogBox.getPosition().y));
	battleLogBlocker.setPosition(sf::Vector2f(battleLogBox.getPosition().x, 250));
	battleLogBlocker.setFillColor(sf::Color::Black);
	endTurnButton.setCharacterSize(15);
	endTurnButton.setFont(GameManager::font);
	endTurnButton.setString("End Turn");
	endTurnButton.setPosition(WINDOW_WIDTH - endTurnButton.findCharacterPos(8).x - 50, WINDOW_HEIGHT / 2);
}

//Displays battle UI
void Battle::displayUI(sf::RenderWindow *window) {
	updateLog(window);
	window->draw(battleLogBlocker);
	currentPlayer->drawHand(window);
	currentPlayer->displayUI(window);
	window->draw(endTurnButton);
}
