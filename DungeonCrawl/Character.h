#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Character {
public:
	//character stats
	int maxHealth; //Max hp character has, can be replenished with health potions (maybe healing spell too)
	int currentHealth; //Current hp

	int maxMana; //Used to cast spells, can be replenished with mana potions
	int currentMana; //Amount of mana currently available

	int accuracy; //Determines likelihood of landing attacks and crit chance
	int dexterity; //used to determine likelihood of dodging enemy attacks and chance for initiative

	int totalDefense; //Will be calculated using player armor, or default value for enemies

	int numFrags; //Fragments of "memory" are absorbed upon killing enemies, used as currency

	//********************************FUNCTIONS BELOW HERE*************************************************

	//Constructor
	Character(int hp, int mna, int totdef, int frags, int acc, int dex);

	//Decrease or increase health by given amount, not going below zero or above max
	void takeDamage(int amt);
	void restoreHealth(int amt);

	//Decrease or increase mana by given amount, not going below zero or above max
	void useMana(int amt);
	void restoreMana(int amt);

	//Maybe player and enemy have their own attack functions?
	//void attack(Character attacker, Character victim);
};