#include "Character.h"

Character::Character(int hp, int mna, int totdef, int frags, int acc, int dex) {
	maxHealth = hp;
	currentHealth = hp;

	maxMana = mna;
	currentMana = mna;

	accuracy = acc;
	dexterity = dex;

	totalDefense = totdef;

	numFrags = frags;
}

void Character::takeDamage(int amt) {
	if (currentHealth - amt < 0)
		currentHealth = 0;
	else
		currentHealth -= amt;
}
void Character::restoreHealth(int amt) {
	if (currentHealth + amt > maxHealth)
		currentHealth = maxHealth;
	else
		currentHealth += amt;
}

void Character::useMana(int amt) {
	if (currentMana - amt < 0)
		currentMana = 0;
	else
		currentMana -= amt;
}
void Character::restoreMana(int amt) {
	if (currentMana + amt > maxMana)
		currentMana = maxMana;
	else
		currentMana += amt;
}