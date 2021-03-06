#include "GameManager.h"
#include "Player.h"
#include "Battle.h"

sf::Font GameManager::font;

GameManager::GameManager(int width, int height) {
	window.create(sf::VideoMode(width, height),"Cards!");
	if (font.loadFromFile("Fonts/light_pixel-7.ttf")) {
	}
	else {
		LOG("COULD NOT LOAD FONT");
	}
}

int GameManager::getWindowWidth() const {
	return window.getSize().x;
}

int GameManager::getWindowHeight() const {
	return window.getSize().y;
}

void GameManager::Start() {
	Player p1("Player 1");
	Player p2("Player 2");
	std::cout << "Player name: " << p1.getName() << "\nPlayer energy: " << p1.getEnergy() << "\nPlayer Inventory Size: " << p1.getInventory()->size() << std::endl;

	for (int i = 0;i < 10;i++) {
		p1.addCardDeck(new MagmaWarrior);
		p2.addCardDeck(new MagmaWarrior);
	}
	Battle b(&p1, &p2);
	b.Start(&window);
	std::cout << "Player Inventory Size: " << p1.getInventory()->size();
	/*p1.removeCardInventory();
	std::cout << "Player Inventory Size: " << p1.getInventory()->size();*/
	//std::cin.get();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		window.display();
	}
}

GameManager::~GameManager() {
	
}