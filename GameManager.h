#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <thread>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define LOG(x) std::cout<<x<<std::endl;

class GameManager{
public:
	GameManager(int, int);
	void Start();
	int getWindowWidth() const;
	int getWindowHeight() const;

	static sf::Font font;
	~GameManager();
private:
	sf::RenderWindow window;
	sf::Clock dt;
};