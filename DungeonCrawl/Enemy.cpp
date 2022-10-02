#include "Enemy.h"
#include "Player.h"
using namespace std;


void Enemy::displayStats() {
	cout << name << endl;
	cout << "Hp and Mana: " << currentHealth << ", " << currentMana << endl;
	cout << "Defense Value: " << totalDefense << endl;
	cout << "Accuracy and Dex: " << accuracy << ", " << dexterity << endl;
	cout << "Num frags: " << numFrags << endl << endl;
}

void Enemy::attackPlayer(Character& player, int level) {
	int hitChance = rand() % 100 + 1; //Random num in range 1 to 100
	if (hitChance > (70 + Character::accuracy - player.dexterity)) {
		cout << "Enemy Attack missed!" << endl;
	}
	else {
		cout << "Enemy Attack Hit!" << endl;
		//FIXME:int damage = determineDamage(enemy.totalDefense);

		int damage = attack; //Base damage value
		damage += rand() % level + 1; //Creates random number in range of 1 to level for damage variation
		damage -= player.totalDefense;
		/*if (weapon.elementalType != "None") {
			int elemDmg = rand() % (weapon.elementalDamage / 2) + weapon.elementalDamage / 2 + 1; //range of elemdmg/2 to elemdmg
			damage += elemDmg;
		}
		//FIXME
		if (RESISTANT) {
			elemDmg -= elemDmg / 2;
		}
		else if (WEAK) {
			elemDmg += elemDmg / 2;
		}
		*/

		//FIXME: Above is determine damage function, make the function call work^^^

		if (hitChance <= Character::accuracy) {
			cout << "Critical hit!!" << endl;
			player.currentHealth -= (2 * damage); //subtract damage times crit multiplier (2?) from enemy health
		}
		else {
			player.currentHealth -= damage;
		}
		cout << damage << " damage dealt. Player health is " << player.currentHealth << endl;
	}
}