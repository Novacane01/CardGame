#include "Battle.h"

Battle::Battle(Player *player1, Player *player2) {
	players[0] = player1;
	players[1] = player2;
}

void Battle::Start() {
	std::vector<Card> *deck1 = players[0]->getDeck();
	std::vector<Card> *deck2 = players[1]->getDeck();
	std::vector<Card> hand1;
	std::vector<Card> hand2;

	//***Initial Draw Phase***//
	phase = PHASE::DRAW;

	for (int i = 0;i < initCardstoDraw;i++) {
		Draw(&hand1, deck1);
		Draw(&hand2, deck2);
	}

	//***Incrementing Phase***//
	nextPhase();

	//***Battle Loop***//
	while (!gameIsWon) {
		if (phase == PHASE::DRAW) {
			Draw()
		}
	}
}

void Battle::Draw(std::vector<Card>* hand, std::vector<Card>* deck) {
	hand->push_back(deck->back());
}

void Battle::nextPhase() {
	int phaseNum = static_cast<int>(phase);
	if (phaseNum != 5) {
		phaseNum++;
	}
	else {
		phaseNum = 0;
	}
	phase = static_cast<PHASE>(phaseNum);
}