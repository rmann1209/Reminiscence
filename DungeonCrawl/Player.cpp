#include "Player.h"
#include "Enemy.h"
using namespace std;


void Player::displayWeaponStats() {
	cout << "Weapon Type and rarity: " << weapon.weaponType  << "(" << weapon.rarity << ")" << endl;
	cout << "Base damage: " << weapon.baseDamage << endl;
	cout << "Elem type and dmg: " << weapon.elementalType << ", " << weapon.elementalDamage << endl;
	cout << "Flavor text: " << weapon.flavorText << endl << endl;
}

void Player::displayArmorStats(Armor armor) {
	cout << "Armor Type and rarity: " << armor.armorType << "(" << armor.rarity << ")" << endl;
	cout << "Base protection: " << armor.baseProtection << endl;
	cout << "Flavor text: " << armor.flavorText << endl << endl;
}
void Player::displayAllArmor() {
	displayArmorStats(helm);
	displayArmorStats(chestplate);
	displayArmorStats(gauntlets);
	displayArmorStats(boots);
	cout << "TOTAL DEFENSE: " << totalDefense << endl << endl;
}

void Player::replaceWeapon(Weapon& weap) {
	weapon = weap;
}
void Player::replaceHelm(Armor& armor) {
	totalDefense -= helm.baseProtection;
	helm = armor;
	totalDefense += helm.baseProtection;
}
void Player::replaceChestplate(Armor& armor) {
	totalDefense -= chestplate.baseProtection;
	chestplate = armor;
	totalDefense += chestplate.baseProtection;
}
void Player::replaceGauntlets(Armor& armor) {
	totalDefense -= gauntlets.baseProtection;
	gauntlets = armor;
	totalDefense += gauntlets.baseProtection;
}
void Player::replaceBoots(Armor& armor) {
	totalDefense -= boots.baseProtection;
	boots = armor;
	totalDefense += boots.baseProtection;
}

void Player::increaseStrength(int amt) {
	strength += amt;
}


int Player::determineDamage(int totDef) {
	int damage = weapon.baseDamage - totDef; //Base damage value
	damage += rand() % strength+1; //Creates random number in range of 1-strength
	
	if (weapon.elementalType != "None") {
		int elemDmg = rand() % (weapon.elementalDamage / 2) + weapon.elementalDamage / 2 + 1; //range of elemdmg/2 to elemdmg

		//FIXME
		/*if (RESISTANT) {
			elemDmg -= elemDmg / 2;
		}
		else if (WEAK) {
			elemDmg += elemDmg / 2;
		}
		*/

		damage += elemDmg;
	}


	return damage;
}

void Player::attackTarget(Character& enemy) {
	int hitChance = rand() % 100 + 1; //Random num in range 1 to 100
	if (hitChance > (70 + Character::accuracy - enemy.dexterity)) {
		cout << "Attack missed!" << endl;
	}
	else {
		cout << "Attack Hit!" << endl;
		//FIXME:int damage = determineDamage(enemy.totalDefense);

		int damage = weapon.baseDamage - enemy.totalDefense; //Base damage value
		damage += rand() % strength + 1; //Creates random number in range of 1-strength

		if (hitChance <= Character::accuracy) {
			cout << "Critical hit!!" << endl;
			damage *= 2; //FIXME: Should crit multiplier be less?
		}
		
		//Elemental damage will not be doubled on a crit
		if (weapon.elementalType != "None") {
			int elemDmg = rand() % (weapon.elementalDamage / 2) + weapon.elementalDamage / 2 + 1; //range of elemdmg/2 to elemdmg
			damage += elemDmg;
		}
		//FIXME
		/*if (RESISTANT) {
			elemDmg -= elemDmg / 2;
		}
		else if (WEAK) {
			elemDmg += elemDmg / 2;
		}
		*/

		enemy.currentHealth -= damage; //subtract damage from enemy health
		cout << damage << " damage dealt. Enemy health is " << enemy.currentHealth << endl;
	}
}
