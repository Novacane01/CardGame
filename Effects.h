#pragma once
#include "Player.h"

class Effects {
public:	
	static void drawCard(Player *);
	static void gainLife(Player *, int);
	static void discardCard(Player *, Card *);
	static void boostStats(CreatureCard *, int, int); 
private:
};