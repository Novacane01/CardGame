#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "Battle.h"

int main() {
	
	GameManager game(WINDOW_WIDTH, WINDOW_HEIGHT);
	game.Start();
	return 0;
}