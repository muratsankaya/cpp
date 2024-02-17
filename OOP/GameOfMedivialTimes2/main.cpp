/*
  hw3.cpp
  spring 2022
  a game of medieval times
  Murat Sankaya
*/


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrior);

	class Weapon {
		friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);

	public:
		Weapon (const string& weaponName, int weaponStrenght) : 
			weaponName(weaponName), weaponStrenght(weaponStrenght) {}
	
		//I will return the strength of the weapon
		int getStrenght() const {
			return weaponStrenght;
		}
		
		//I will set new strength of the weapons, after the battle
		//Both strenghts could be equal as well
		void setStrenght(Weapon& weakerWeapon){
			weaponStrenght -= weakerWeapon.weaponStrenght;
			weakerWeapon.weaponStrenght = 0;
		}

	private:
		string weaponName;
		int weaponStrenght;
	};

	friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);

public:
	Warrior(const string& warriorName, const string& weaponName, int weaponStrenght) :
		name(warriorName), weapon(weaponName, weaponStrenght) {}

	//To access warrior's name 
	const string& getName() const {
		return name;
	}

	//To return the weapon's strenght 
	int getStrenght() const {
		return weapon.getStrenght();
	}

	//To let warriors battle 
	void Battle(Warrior& warrior) {
		if (weapon.getStrenght() == warrior.weapon.getStrenght()) {
			cout << "Mutual Anhiliation: " << name << " and " << warrior.name <<
				" die at each other's hands" << endl;
			weapon.setStrenght(warrior.weapon);
		}
		else if (weapon.getStrenght() > warrior.weapon.getStrenght()) {
			cout << name << " defeats " << warrior.name << endl;
			weapon.setStrenght(warrior.weapon);
		}
		else {
			cout << warrior.name << " defeats " << name << endl;

			//In this case the other warrior's strenght is greater
			warrior.weapon.setStrenght(weapon);
		}
	}

	
private:
	string name;
	Weapon weapon;

};

//to open the stream
void openFile(ifstream& ifs);

//to  search for warrior
size_t warriorSearch(const vector<Warrior>& warField, const string& warriorName);

//to add warriors
void addWarrior(ifstream& ifs, vector<Warrior>& warField);

//to display the war's status
void displayStatus(const vector<Warrior>& warField);

//to check if the warriors already exsist
bool inTheWar(size_t warrior1Index, size_t warrior2Index, const vector<Warrior>& warField,
	const string& warrior1Name, const string& warrior2Name);

//to check if they are alive
bool areAlive(size_t warrior1Index, size_t warrior2Index, const vector<Warrior>& warField);

//to structure the battle
void battleWarriors(ifstream& ifs, vector<Warrior>& warField);

 
int main() {
	vector<Warrior> warField;
	ifstream ifs;
	openFile(ifs);
	string command;
	while (ifs >> command) {
		if (command == "Warrior") {
			addWarrior(ifs, warField);
		}
		else if (command == "Status") {
			displayStatus(warField);
		}
		else {
			battleWarriors(ifs, warField);
		}
	}
	ifs.close();
}

//overloading the output operator for the weapon class
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
	os << "weapon: " << weapon.weaponName << ", " << weapon.weaponStrenght;
	return os;
}

//overloading the output operator for the warrior class
ostream& operator<<(ostream& os, const Warrior& warrior) {
	os << "Warrior: " << warrior.name << ", " << warrior.weapon;
	return os;
}

void openFile(ifstream& ifs) {
	ifs.open("warriors.txt");
	if (!ifs) {
		cerr << "File could not be found!";
		ifs.clear();
		exit(1);
	}
}

//To check if the warrior is already in the way
size_t warriorSearch(const vector<Warrior>& warField, const string& warriorName) {
	for (size_t i = 0; i < warField.size(); ++i) {
		if (warField[i].getName() == warriorName) {
			return i;
		}
	}
	return warField.size();
}

//Adding warrior to the vector of warriors
void addWarrior(ifstream& ifs, vector<Warrior>& warField) {
	string warriorName, weaponName;
	int weaponStrenght;
	ifs >> warriorName >> weaponName >> weaponStrenght;
	//If the warrior search returns a value that is out of range, I will add the warrior to the vector
	if (warriorSearch(warField, warriorName) == warField.size()) {
		warField.emplace_back(warriorName, weaponName, weaponStrenght);
	}
	else {
		cerr << warriorName << " is already in the war!" << endl;
	}
}

//displaying war status using the output operator defined for the classes
void displayStatus(const vector<Warrior>& warField) {
	cout << "There are: " << warField.size() << " warriors" << endl;
	for (const Warrior& warrior : warField) {

		cout << warrior << endl;
		////cout << warrior.operator<<(cout);
		//iostream c();
		//cout.operator<<(warrior) << endl;
	}
}

//Checking if the warrior's already exsist
//In this case I had to pass warrior names as well, because they may not exsist in the warField vector
//and my intention is to mention their names in the error messsege
bool inTheWar(size_t warrior1Index, size_t warrior2Index, const vector<Warrior>& warField,
	const string& warrior1Name, const string& warrior2Name) {
	if (warrior1Index == warField.size() && warrior2Index == warField.size()) {
		cout << warrior1Name << " and " << warrior2Name <<
			" are not in the war!" << endl;
		return false;
	}
	else if (warrior1Index == warField.size()) {
		cout << warrior1Name << " is not in the war!" << endl;
		return false;
	}
	else if (warrior2Index == warField.size()) {
		cout << warrior2Name << " is not in the war!" << endl;
		return false;
	}
	return true;
}

//Checking if the warriors are alive
bool areAlive(size_t warrior1Index, size_t warrior2Index, const vector<Warrior>& warField) {
	if (warField[warrior1Index].getStrenght() == 0 && warField[warrior2Index].getStrenght() == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return false;
	}
	else if (warField[warrior2Index].getStrenght() == 0) {
		cout << "He is dead, " << warField[warrior1Index].getName() << endl;
		return false;
	}
	else if (warField[warrior1Index].getStrenght() == 0) {
		cout << "He is dead, " << warField[warrior2Index].getName() << endl;
		return false;
	}
	return true;
}


//structuring the battle
void battleWarriors(ifstream& ifs, vector<Warrior>& warField) {
	string warrior1Name, warrior2Name;
	ifs >> warrior1Name >> warrior2Name;

	//Instead of searching for the warrior's name each time, I thought passing indexes would be more efficient
	size_t warrior1Index = warriorSearch(warField, warrior1Name);
	size_t warrior2Index = warriorSearch(warField, warrior2Name);

	if (inTheWar(warrior1Index, warrior2Index, warField, warrior1Name, warrior2Name)) {
		cout << warrior1Name << " battles " << warrior2Name << endl;
		if (areAlive(warrior1Index, warrior2Index, warField)) {
			warField[warrior1Index].Battle(warField[warrior2Index]);
		}
	}
}
