#pragma once
#include "Character.h"
using namespace std;

class Enemy : public Character {
public:
	int attack;
	string name;

	Enemy(int hp, int mna, int att, int totDef, int frags, int acc, int dex, string n) : Character(hp, mna, totDef, frags, acc, dex) {
		name = n;
		attack = att;
	}

	void displayStats();

	void attackPlayer(Character& player,int level);
};