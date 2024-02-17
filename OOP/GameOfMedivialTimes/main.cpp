/*
  hw2.cpp
  spring 2022
  a game of medieval times
  Murat Sankaya
*/


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


struct Warfield {
	// I will store the names and strengths in sequence
	vector<string> warriorNames;
	vector<int> warriorStrengths;
};


//To open a file
void openFile(ifstream& ifs);

//To add a warrior
void addWarrior(ifstream& ifs, Warfield& war);

//To search for a warrior
size_t warriorSearch(const vector<string>& warrirorNames, const string& name);

//To display the war status
void displayStatus(const Warfield& war);

//To check if the warriors are in the war
bool inTheWar(size_t warrior1Index, size_t warrior2Index, size_t warSize, const string& warrior1,
	const string& warrior2);

//To check if the warriors are alive
bool areAlive(const Warfield& war, size_t warrior1Index, size_t warrior2Index);

//To execute the battle
void battleExecution(Warfield& war, size_t warrior1Index, size_t warrior2Index);

//To combat warriors
void beginBattle(ifstream& ifs, Warfield& war);


int main() {
	ifstream ifs;

	//Openning the file
	openFile(ifs);
	string command;
	Warfield war;
	while (ifs >> command) {
		if (command == "Warrior") {

			//Adding a warrior
			addWarrior(ifs, war);
		}
		else if (command == "Status") {

			//Displaying the current status of the war
			displayStatus(war);
		}
		else if (command == "Battle") {

			//Trying to execute a battle
			beginBattle(ifs, war);
		}
	}
	ifs.close();
}

//Openning the file
void openFile(ifstream& ifs) {
	ifs.open("warriors.txt");
	if (!ifs) {
		ifs.clear();
		cout << "The intended file could not be found!" << endl;
		exit(1);
	}
}

//Checking if the name already exsists
size_t warriorSearch(const vector<string>& warrirorNames, const string& name) {
	for (size_t i = 0; i < warrirorNames.size(); ++i) {
		if (warrirorNames[i] == name) {
			//If I find the warrior I will return its index
			return i;
		}
	}
	//If I can't find the warrior I will return an index which is out of range
	return warrirorNames.size();
}

//Adding a Warrior 
void addWarrior(ifstream& ifs, Warfield& war) {
	string name;
	int strength;
	ifs >> name >> strength;

	//If the warrior search returns an index which is out of range, that means the warrior is not in the war
	if (warriorSearch(war.warriorNames, name) == war.warriorNames.size()) {
		war.warriorNames.push_back(name); 
		war.warriorStrengths.push_back(strength);
	}
	//Else the warrior is already in the war
	else {
		cerr << name << " is already in the war!" << endl;
	}
}

//Display the current status of the war
void displayStatus(const Warfield& war) {
	cout << "There are: " << war.warriorNames.size() << " warriors" << endl;
	for (size_t i = 0; i < war.warriorNames.size(); ++i) {
		cout << "Warrior: " << war.warriorNames[i] << ", strenght: " << war.warriorStrengths[i] << endl;
	}
}

//Checking if the warriors are in the war
bool inTheWar(size_t warrior1Index, size_t warrior2Index, size_t warSize, const string& warrior1, 
	const string& warrior2) {

	if ( warrior1Index == warSize && warrior2Index == warSize ){
		cerr << warrior1 << " and " << warrior2 << 
			" are not in the war!" << endl;
		return false;
	}
	else if (warrior1Index == warSize) {
		cerr << warrior1 << " is not in the war!" << endl;
		return false;
	}
	else if (warrior2Index == warSize) {
		cerr << warrior2 << " is not in the war!" << endl;
		return false;
	}
	return true;
}

//Checking if the warriros are alive 
bool areAlive(const Warfield& war, size_t warrior1Index, size_t warrior2Index) {
	if (war.warriorStrengths[warrior1Index] == 0 && war.warriorStrengths[warrior2Index] == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return false;
	}
	else if (war.warriorStrengths[warrior2Index] == 0) {
		cout << "He is dead, " << war.warriorNames[warrior1Index] << endl;
		return false;
	}
	else if (war.warriorStrengths[warrior1Index] == 0) {
		cout << "He is dead, " << war.warriorNames[warrior2Index] << endl;
		return false;
	}
	return true;
}

//Executing the battle
void battleExecution(Warfield& war, size_t warrior1Index, size_t warrior2Index) {
	if (war.warriorStrengths[warrior1Index] == war.warriorStrengths[warrior2Index]) {
		cout << "Mutual Annihilation: " << war.warriorNames[warrior1Index] << " and " <<
			war.warriorNames[warrior2Index] << " die at each other's hands" << endl;
		war.warriorStrengths[warrior1Index] = 0;
		war.warriorStrengths[warrior2Index] = 0;
	}
	else if (war.warriorStrengths[warrior1Index] > war.warriorStrengths[warrior2Index]) {
		cout << war.warriorNames[warrior1Index] << " defeats " << war.warriorNames[warrior2Index] << endl;
		war.warriorStrengths[warrior1Index] -= war.warriorStrengths[warrior2Index];
		war.warriorStrengths[warrior2Index] = 0;
	}
	else {
		cout << war.warriorNames[warrior2Index] << " defeats " << war.warriorNames[warrior1Index] << endl;
		war.warriorStrengths[warrior2Index] -= war.warriorStrengths[warrior1Index];
		war.warriorStrengths[warrior1Index] = 0;
	}
}

//Letting the warriors fight
void beginBattle(ifstream& ifs, Warfield& war) {
	string warrior1, warrior2;
	ifs >> warrior1 >> warrior2;

	//Instead of doing too many warrior searches I thought passing indicies is less work
	size_t warrior1Index = warriorSearch(war.warriorNames, warrior1);
	size_t warrior2Index = warriorSearch(war.warriorNames, warrior2);
	size_t warSize = war.warriorNames.size();

	//Checking if the warriors exsist
	if (inTheWar(warrior1Index, warrior2Index, warSize, warrior1, warrior2)){
		cout << warrior1 << " battles " << warrior2 << endl;

		//If they exsist, are they alive
		if (areAlive(war, warrior1Index, warrior2Index)) {

			//If both are alive, execute the battle
			battleExecution(war, warrior1Index, warrior2Index);

		}
	}
}
