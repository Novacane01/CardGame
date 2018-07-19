#include "GameManager.h"

GameManager::GameManager(int width, int height) {
	window.create(sf::VideoMode(width, height),"Cards!");
}

int GameManager::getWindowWidth() const {
	return window.getSize().x;
}

int GameManager::getWindowHeight() const {
	return window.getSize().y;
}

void GameManager::Start() {

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

}

GameManager::~GameManager() {
	
}