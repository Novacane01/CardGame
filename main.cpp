#include <iostream>
#include "Player.h"
#include "Battle.h"

int main() {
	//int width = 1920, height = 1080;
	//GameManager game(width, height);
	Player p1("Player 1");
	Player p2("Player 2");
	std::cout << "Player name: " << p1.getName() << "\nPlayer energy: " << p1.getEnergy() << "\nPlayer Inventory Size: " << p1.getInventory()->size() << std::endl;

	for (int i = 0;i < 10;i++) {
		p1.addCardDeck(new MagmaWarrior);
		p2.addCardDeck(new MagmaWarrior);
	}
	Battle b(&p1, &p2);
	b.Start();
	std::cout << "Player Inventory Size: " << p1.getInventory()->size();
	/*p1.removeCardInventory();
	std::cout << "Player Inventory Size: " << p1.getInventory()->size();*/
	std::cin.get();
	return 0;
}