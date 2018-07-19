#pragma once
#include "SFML\Graphics.hpp"

class GameManager{
public:
	GameManager(int, int);
	void Start();
	int getWindowWidth() const;
	int getWindowHeight() const;
	~GameManager();
private:
	sf::RenderWindow window;
	sf::Clock dt;
};