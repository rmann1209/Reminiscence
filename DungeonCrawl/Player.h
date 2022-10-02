#pragma once
#include "Character.h"
using namespace std;

class Player : public Character {
public:

	struct Weapon {
		string weaponType;
		int baseDamage;

		string elementalType;
		int elementalDamage;

		string rarity;
		string flavorText;

		Weapon() {
			baseDamage = 0;
			elementalDamage = 0;
		}

		Weapon(string weapType, int baseDmg, string elemType, int elemDmg, string rare, string flvrText) {
			weaponType = weapType;
			baseDamage = baseDmg;
			elementalType = elemType;
			elementalDamage = elemDmg;
			rarity = rare;
			flavorText = flvrText;
		}

		//NEED BIG THREE SO I CAN OVERWRITE VARIABLES IN MAIN WITH NEW STATS
		Weapon(const Weapon& otherWeap) {
			weaponType = otherWeap.weaponType;
			baseDamage = otherWeap.baseDamage;
			elementalType = otherWeap.elementalType;
			elementalDamage = otherWeap.elementalDamage;
			rarity = otherWeap.rarity;
			flavorText = otherWeap.flavorText;
		}

		Weapon& operator=(const Weapon& otherWeap) {
			weaponType = otherWeap.weaponType;
			baseDamage = otherWeap.baseDamage;
			elementalType = otherWeap.elementalType;
			elementalDamage = otherWeap.elementalDamage;
			rarity = otherWeap.rarity;
			flavorText = otherWeap.flavorText;
			return *this;
		}

		~Weapon() {

		}
	};

	struct Armor {
		string armorType;
		int baseProtection;

		string rarity;
		string flavorText;

		Armor() {
			baseProtection = 0;
		}

		Armor(string amrType, int baseProt, string rare, string flvrText) {
			armorType = amrType;
			baseProtection = baseProt;
			rarity = rare;
			flavorText = flvrText;
		}

		Armor(const Armor& otherArmor) {
			armorType = otherArmor.armorType;
			baseProtection = otherArmor.baseProtection;
			rarity = otherArmor.rarity;
			flavorText = otherArmor.flavorText;
		}

		Armor& operator=(const Armor& otherArmor) {
			armorType = otherArmor.armorType;
			baseProtection = otherArmor.baseProtection;
			rarity = otherArmor.rarity;
			flavorText = otherArmor.flavorText;
			return *this;
		}

		~Armor() {

		}
	};

	int strength; //Player strength, used as damage modifier (added on to base damage) (maybe carry weight too?)

	short memoriesUnlocked; //Number of player memories unlocked by killing miniBosses

	Weapon weapon;

	Armor helm;
	Armor chestplate;
	Armor gauntlets;
	Armor boots;

	//Constructs a player objects and initializes all variables
	Player(int hp, int mna, int frags, int acc, int dex, int str, Weapon weap, Armor hlm, Armor chest, Armor gaunt, Armor bts) : Character(hp, mna, 0, frags, acc, dex) {
		strength = str;

		numFrags = frags;
		memoriesUnlocked = 0;

		weapon = weap;

		helm = hlm;
		chestplate = chest;
		gauntlets = gaunt;
		boots = bts;

		//FIXME: Test this!! Should overwrite "0" totalDef passed to character with actual number based on armor
		totalDefense = helm.baseProtection + chestplate.baseProtection + gauntlets.baseProtection + boots.baseProtection;
	}

	//will display stats of weapon, armor, or all armor
	void displayWeaponStats();
	void displayArmorStats(Armor armor);
	void displayAllArmor();

	//Replace either weapon or specific piece of armor with whatever reference is passed in
	void replaceWeapon(Weapon& weapon);
	void replaceHelm(Armor& armor);
	void replaceChestplate(Armor& armor);
	void replaceGauntlets(Armor& armor);
	void replaceBoots(Armor& armor);

	//Increase strength stat by given amount
	void increaseStrength(int amt);


	//Use weapon base damage and add random value from 0 to strength for total damage
	//Add elemental damage if applicable, use multiplier if weak/resistant
	//Then, subtract by enemy totDef amount (rng from half to full totDef, which is passed from function below)
	int determineDamage(int totDef);

	//First, determine if successful hit (1-100 rng, if num <= acc then crit)
	//Pass enemy totDef to determineDamage() and subtract value from enemy current health
	void attackTarget(Character& enemy);
};