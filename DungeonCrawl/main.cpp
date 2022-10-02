#include "Player.h"
#include "Tester.h"
#include "Character.h"
#include "Enemy.h"
using namespace std;

/* THIS IS ANOTHER WAY OF INITIALIZING ALL ENEMIES AND STORING IN VECTOR
void initializeEnemies(vector <Enemy>& enem) {
	int numEnems = 6; //INCREASE IF NUM ENEMIES IS CHANGED
	for (int i = 0; i < numEnems; i++) {
		Enemy e(20, 0, 21, 10, 24, 1, 2, "Skeleton");
		enem.push_back(e);
	}
}
*/

void readEnemyFile(string fileName, vector <Enemy>& enem) {
	ifstream file(fileName);
	if (file.is_open()) {
		string line;
		getline(file, line);
		while (getline(file, line, ',')) {
			string name = line;

			getline(file, line, ',');
			int hp = stoi(line);

			getline(file, line, ',');
			int mana = stoi(line);

			getline(file, line, ',');
			int attack = stoi(line);

			getline(file, line, ',');
			int totDef = stoi(line);

			getline(file, line, ',');
			int frags = stoi(line);

			getline(file, line, ',');
			int acc = stoi(line);

			getline(file, line);
			int dex = stoi(line);

			Enemy enemy(hp, mana, attack, totDef, frags, acc, dex, name);
			enem.push_back(enemy);
		}
	}
	file.close();
}

//Initialize weaponTypes list with all potential weapon types
void initializeWeaponTypes(vector <string>& weaponTypes) {
	weaponTypes.push_back("Sword");
	weaponTypes.push_back("Battleaxe");
	weaponTypes.push_back("Mace");
	weaponTypes.push_back("Warhammer");
	weaponTypes.push_back("Katana");
}

//using the vector of weapon names and current level, create a new generic weapon of random type/dmg/elemental effects
//Returns the weapon that was created
Player::Weapon createWeapon(vector <string>& weaponTypes, int level) {
	//Randomizes dmg modifier based on current level
	int dmgMod = (rand() % (level/2)) + level/2 + 1; //Creates random number with min = level/2 and max = level, inlcusive
	cout << "TEST RANDOM DMG MOD: " << dmgMod << endl;

	//Randomizes weapon type
	int randName = rand() % weaponTypes.size();
	string name = weaponTypes.at(randName);
	cout << "TEST RANDOM NAME: " << name << endl;

	//TO DO: Randomize elemental effect (Higher chances at later levels)
	//TO DO: Randomize rarity (Better at later levels)
	//TO DO: Create Flavor Text for weapon (Maybe have first sentence describe weapon type and material (Better material for better rarity)...
	//... Second sentence will describe elemental effect if any, then concatenate into one string

	Player::Weapon tempWeapon(name, 20 + dmgMod, "None", 0, "Common", "A worn iron sword. Simple, yet effective."); //FIXME: everything in parentheses should be variable

	return tempWeapon;
}

void initializeArmorTypes(vector <string>& armorTypes) {
	armorTypes.push_back("Helm");
	armorTypes.push_back("Chestplate");
	armorTypes.push_back("Gauntlets");
	armorTypes.push_back("Boots");
}

//FIXME: not done!
Player::Armor createArmor(vector <string>& armorTypes, int level) {
	//Randomizes armor type
	int randType = rand() % armorTypes.size();
	string type = armorTypes.at(randType);
	cout << "TEST RANDOM TYPE: " << type << endl;

	//Randomizes protection modifier based on current level
	int protMod = (rand() % (level/2 + 1)) + level / 2; //Creates random number with min = level/2 and max = level, inlcusive
	cout << "TEST RANDOM PROT MOD: " << protMod << endl;

	Player::Armor tempArmor(type, protMod, "Common", "FLAVORTEXT"); //FIXME
	return tempArmor;
}

//Find next encounter, and update chances of each based on results. If merchantLevel (or 1 after), do merchant (or boss)
string decideNextEncounter(int& battleChance, int& lootChance, int& merchantLevel, int& level) {
	level++;
	int randNum = rand() % 101; //Random number from 0 to 100
	//cout << "RAND NUM: " << randNum << endl;

	if (level == merchantLevel) {
		battleChance = 80;
		lootChance = 20;
		return "Merchant";
	}
	else if (level == merchantLevel + 1) {
		merchantLevel += 7 + rand() % 3;
		return "Boss";
	}
	else if (level == 1 || randNum < battleChance) {
		battleChance -= 20;
		lootChance += 20;
		return "Battle";
	}
	else {
		battleChance = 80;
		lootChance = 20;
		return "Loot";
	}
}

Enemy decideEnemy(vector <Enemy> enemies) {
	int randNum = rand() % enemies.size();
	return enemies.at(randNum);
}

void printPathOptions() {
	cout << endl << "You see a path open before you. What would you like to do?" << endl;
	cout << "1. Go Forward" << endl;
	cout << "2. View Inventory" << endl;
	cout << "0. End Game" << endl;
}

//Return true if player wins initiative, otherwise false
bool decideInitiative(Player& player, Enemy& enemy) {
	int initiative = rand() % 100 + 1; //rand num from 1 to 100

	//Player starts (true) if roll is <= to 50 plus player dex - enemy dex
	if (initiative <= 50 + player.dexterity - enemy.dexterity)
		return true;
	else
		return false;
}

void printCombatOptions() {
	cout << endl << "What would you like to do?" << endl;
	cout << "1. Attack" << endl;
	cout << "2. Cast Spell" << endl;
	cout << "3. Use Item" << endl;
}

int main() {
	srand((unsigned)time(0)); //FIXME: Once random values are selected, they do not change with future calls of this function

	bool gameOver = false; //Once true, program will terminate
	bool nextLevel = false; //Will be false until new room is chosen, true for one loop, then back to false

	int level = 0; //Starting at 0, increases with each room
	string currentRoom = "Nothing"; //Can be loot, battle, merchant, nothing, maybe others...
	int battleChance = 70; //Out of 100, will decrease after each consecutive battle and reset once another room is chosen
	int lootChance = 25; //Out of 100, will decrease after each consecutive loot discovery and reset after battle.
	int merchantLevel = 7 + rand() % 3; //Will increase slowly over time, but will not be possible until at least level... 5?

	vector <Enemy> enemies1; //Stores the enemies of difficulty 1

	vector <string> weaponTypes; //Stores the names of possible weapons to be created
	initializeWeaponTypes(weaponTypes);

	vector <string> armorTypes; //Stores the names of possible armor types to be created
	initializeArmorTypes(armorTypes);

	//Initialize starting weapon and armor pieces
	Player::Weapon startWeapon("Sword", 20, "None", 0, "Common", "A worn iron sword. Simple, yet effective.");
	Player::Armor startHelm("Helm", 3, "Common", "Leather straps barely held together, roughly in the shape of a helmet");
	Player::Armor startChestplate("Chestplate", 5, "Common", "A large leather tunic that offers barely more protection than the fabric of your shirt...");
	Player::Armor startGauntlets("Gauntlets", 2, "Common", "A crumbling pair of leather gloves");
	Player::Armor startBoots("Boots", 2, "Common", "A mismatched pair of old leather boots");
	
	//Initialize player
	Player player(50, 50, 0, 5, 5, 5, startWeapon, startHelm, startChestplate, startGauntlets, startBoots);

	player.displayWeaponStats();
	player.displayAllArmor();


	//FIXME: Initialize enemy for testing purposes
	readEnemyFile("Enemies/Tier1Enemies.txt", enemies1);
	//Test to make sure file is properly read and enemy is created and stored
	for (unsigned int i = 0; i < enemies1.size(); i++) {
		enemies1.at(i).displayStats();
	}

	/*
	for (int i = 0; i < 10; i++) {
		currentRoom = decideNextEncounter(battleChance, lootChance, merchantLevel, level);
		cout << "Current Room: " << currentRoom << endl;
		//cout << "Battle, Loot, Merchant Chances: " << battleChance << ", " << lootChance << ", " << merchantLevel << endl;
		cout << "Level: " << level << endl << endl;
	}
	*/

	cout << endl << "GAME BEGIN!!!!!!!!" << endl;
	cout << "Starting text here..." << endl << endl;
	int userIn;

	//Game is running when within this while loop
	while (!gameOver) {
		printPathOptions();
		cin >> userIn;

		if(userIn == 0){
			gameOver = true;
			break;
		}
		else if(userIn == 1) {
			currentRoom = decideNextEncounter(battleChance, lootChance, merchantLevel, level);
			cout << "Current Room: " << currentRoom << endl;
			cout << "Level: " << level << endl << endl;
		}
		else if (userIn == 2) {
			cout << "FIXME: DISPLAY INVENTORY" << endl;
			continue;
		}

		if (currentRoom == "Battle") {
			bool battleOver = false;

			Enemy enemy = decideEnemy(enemies1);
			enemy.displayStats();

			bool playerTurn = decideInitiative(player, enemy);
			//cout << "Player Turn: " << playerTurn << endl; //0 means enemy turn, 1 means player
			while (!battleOver) {
				if (playerTurn) {
					printCombatOptions();
					cin >> userIn;
					if (userIn == 1) {
						player.attackTarget(enemy);
						if (enemy.currentHealth <= 0) {
							cout << "Enemy Slain" << endl;
							battleOver = true;
							player.numFrags += enemy.numFrags;
							cout << "Player has gained " << enemy.numFrags << " fragments. New total: " << player.numFrags << endl;
						}
					}
					playerTurn = false;
				}
				else {
					//Enemy Attack
					cout << endl << "**ENEMY TURN START**" << endl << endl;
					enemy.attackPlayer(player, level);
					if (player.currentHealth <= 0) {
						battleOver = true;
						gameOver = true;
						cout << "Player has died..." << endl;
					}
					playerTurn = true;
				}
			}
		}
	}

	cout << "Game has ended" << endl;
	return 0;
}