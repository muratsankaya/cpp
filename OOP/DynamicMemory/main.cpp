
/*
  hw05.cpp
  Spring 2022
  Dynamic Memory
  Murat Sankaya
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


// Your Noble and Warrior classes should go here.
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    Warrior(const string& name, double strength) : name(name), strength(strength), hired(false) {};

    const string& getName() const { return name; }

    double getStrength() const { return strength; }

    void setHire() { hired = true; }

    void setFree() { hired = false; }

    //To check if the warrior is employed
    bool isHired() const { return hired; }

    void setStrenght(double newStrenghtFraction) {
        strength *= newStrenghtFraction;
    }

private:
    string name;
    double strength;
    bool hired;    //Either employed or free 
};

class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble);
public:
    Noble(const string& name) : name(name), isAlive(true), armyStrength(0) {};

    const string& getName() const { return name; }

    void battle(Noble& opponent) {
        if (&opponent != this) {
            cout << name << " battles " << opponent.name << endl;
            if (areAlive(opponent)) {
                if (armyStrength >= opponent.armyStrength) {

                    this->setWarriorsStrength(1 - (opponent.armyStrength / armyStrength));

                    opponent.setWarriorsStrength(0);

                    //At this method I'm also setting the weaker strength to 0 !!!
                    this->setStrength(opponent.armyStrength);

                    opponent.isAlive = false;
                    //If the army strenghts are equal, both nobles are dead and their armyies are destroyed
                    if (armyStrength == opponent.armyStrength) {
                        this->isAlive = false;
                        cout << "Mutual Annihilation: " << name << " and " << opponent.name << " die at each other's hands." << endl;
                    }
                    else {
                        cout << name << " defeats " << opponent.name << endl;
                    }
                }
                else {

                    opponent.setWarriorsStrength(1 - (armyStrength / opponent.armyStrength));

                    this->setWarriorsStrength(0);

                    //At this method I'm also setting the weaker strength to 0 !!!
                    opponent.setStrength(this->armyStrength);

                    this->isAlive = false;

                    cout << opponent.name << " defeats " << name << endl;
                }
            }
        }
        else { cout << name << " will not fight himself!" << endl; }
    }

    bool hire(Warrior& warrior) {
        if (isAlive) {
            if (warrior.isHired()) {
                cout << warrior.getName() << " already fights for another Noble! " << endl;
                return false;
            }
            else {
                army.push_back(&warrior);
                updateArmyStrenght(warrior.getStrength());
                //This will mark that the warrior is hired
                warrior.setHire();
                return true;
            }
        }
        else { cout << name << " is dead, he can not hire a warrior!" << endl; return false; }
    }

    bool fire(Warrior& warrior) {
        if (isAlive) {
            size_t warriorIndex = findWarrior(warrior.getName());

            //The warrior may not be in the Noble's amry
            if (warriorIndex == army.size()) {
                cout << warrior.getName() << " does not fight for " << name << '!' << endl; return false;
            }
            else {
                cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << '.' << endl;
                while (warriorIndex + 1 != army.size()) {
                    army[warriorIndex] = army[warriorIndex + 1];
                    ++warriorIndex;
                }
                army.pop_back();

                //I'm passing the warrior strenght as a negative value
                updateArmyStrenght(-warrior.getStrength());
                warrior.setFree();
                return true;
            }
        }
        else { cout << name << " is dead, he can not fire a warrior!" << endl; return false; }
    }


private:
    vector<Warrior*> army;
    string name;
    double armyStrength;
    // I created a isAlive field because in the assignment it is stated that a Noble having 0 armyStrenght doesn't mean he/she is dead.
    bool isAlive;

    //I will keep the weakerstrength on the rhs 
    void setStrength(double& weakerStrength) {
        armyStrength -= weakerStrength;
        weakerStrength = 0;
    }

    void setWarriorsStrength(double fraction) {
        for (Warrior* warrior : army) {
            warrior->setStrenght(fraction);
        }
    }

    size_t findWarrior(const string& name) const {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i]->getName() == name) {
                return i;
            }
        }
        return army.size();
    }

    void updateArmyStrenght(double warriorStrenght) {
        armyStrength += warriorStrenght;
    }

    bool areAlive(const Noble& opponent) const {
        if (!opponent.isAlive && !isAlive) { cout << "Oh, NO! They're both dead! Ycuk!" << endl; return false; }
        else if (!opponent.isAlive) { cout << "He's dead, " << name << endl; return false; }
        else if (!isAlive) { cout << "He's dead, " << opponent.name << endl; return false; }
        return true;
    }
};

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << '\t' << warrior.name << ": " << warrior.strength << endl;
    return os;
}

ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.army.size() << endl;
    for (const Warrior* warriorptr : noble.army) {
        os << *warriorptr;
    }
    return os;
}

void fileOpener(ifstream& ifs);

size_t nobleSearch(const string& name, const vector<Noble*>& nobles);

void createNoble(ifstream& ifs, vector<Noble*>& nobles);

size_t warriorSearch(const string& name, const vector<Warrior*>& warriors);

void createWarrior(ifstream& ifs, vector<Warrior*>& warriors);

void hireWarrior(ifstream& ifs, vector<Noble*>& nobles, vector<Warrior*>& warriors);

void fireWarrior(ifstream& ifs, vector<Noble*>& nobles, vector<Warrior*>& warriors);

void battleNobles(ifstream& ifs, const vector<Noble*>& nobles);

void displayStatus(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);

void clearWar(vector<Noble*>& nobles, vector<Warrior*>& warriors);

int main() {
    ifstream ifs;
    fileOpener(ifs);
    vector<Warrior*> warriors;
    vector<Noble*> nobles;
    string command;
    while (ifs >> command) {
        if (command == "Noble") {
            createNoble(ifs, nobles);
        }
        else if (command == "Warrior") {
            createWarrior(ifs, warriors);
        }
        else if (command == "Hire") {
            hireWarrior(ifs, nobles, warriors);
        }
        else if (command == "Fire") {
            fireWarrior(ifs, nobles, warriors);
        }
        else if (command == "Battle") {
            battleNobles(ifs, nobles);
        }
        else if (command == "Status") {
            displayStatus(nobles, warriors);
        }
        else if (command == "Clear") {
            clearWar(nobles, warriors);
        }
    }
    ifs.close();
}

void fileOpener(ifstream& ifs) {
    ifs.open("nobleWarriors.txt");
    if (!ifs) {
        cout << "The inteded file could not be found!" << endl;
        ifs.clear();
        exit(1);
    }
}

size_t nobleSearch(const string& name, const vector<Noble*>& nobles) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == name) {
            return i;
        }
    }
    return nobles.size();
}

void createNoble(ifstream& ifs, vector<Noble*>& nobles) {
    string name;
    ifs >> name;
    if (nobleSearch(name, nobles) == nobles.size()) {
        nobles.push_back(new Noble(name));
    }
    else { cout << "Noble name: " << name << ", is already used by another Noble! " << endl; }
}

size_t warriorSearch(const string& name, const vector<Warrior*>& warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getName() == name) {
            return i;
        }
    }
    return warriors.size();
}

void createWarrior(ifstream& ifs, vector<Warrior*>& warriors) {
    string name;
    int strength;
    ifs >> name >> strength;
    if (warriorSearch(name, warriors) == warriors.size()) {
        warriors.push_back(new Warrior(name, strength));
    }
    else { cout << "Warrior name: " << name << ", is already used by another Warrior! " << endl; }
}

void hireWarrior(ifstream& ifs, vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    string noblename, warriorname;
    ifs >> noblename >> warriorname;
    size_t nobleIndex, warriorIndex;
    nobleIndex = nobleSearch(noblename, nobles), warriorIndex = warriorSearch(warriorname, warriors);

    //first I'm checking if the noble exsists
    if (nobleIndex == nobles.size()) {
        cerr << "Attempting to hire for an unknown noble: " << noblename << endl;
    }
    //then I'm checking if the warrior exsists
    else if (warriorIndex == warriors.size()) {
        cerr << "Attempting to hire using unknown warrior: " << warriorname << endl;
    }
    else {
        //If the hire method returns false 
        if (!nobles[nobleIndex]->hire(*warriors[warriorIndex])) { 
            cerr << "Attempting to hire " << warriorname << " by " << noblename << " failed!" << endl;
        }
    }
}

void fireWarrior(ifstream& ifs, vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    string noblename, warriorname;
    ifs >> noblename >> warriorname;
    size_t nobleIndex, warriorIndex;
    nobleIndex = nobleSearch(noblename, nobles), warriorIndex = warriorSearch(warriorname, warriors);

    //I'm aware that doing the same error checking for hirewarrior function, but I'm displaying different error messeges. Therefore, I did not write a sperate function for that
    //first I'm checking if the noble exsists
    if (nobleIndex == nobles.size()) {
        cerr << "Attempting to fire for an unknown noble: " << noblename << endl;
    }
    //then I'm checking if the warrior exsists
    else if (warriorIndex == warriors.size()) {
        cerr << "Attempting to fire an unknown warrior: " << warriorname << endl;
    }
    else {
        if (!nobles[nobleIndex]->fire(*warriors[warriorIndex])) {
            cerr << "Attempting to fire " << warriorname << " by " << noblename << " failed!" << endl;
        }
    }
}

void battleNobles(ifstream& ifs, const vector<Noble*>& nobles) {
    string noblename1, noblename2;
    ifs >> noblename1 >> noblename2;
    size_t nobleindex1, nobleindex2;
    nobleindex1 = nobleSearch(noblename1, nobles), nobleindex2 = nobleSearch(noblename2, nobles);

    //Checking if the noble exsists
    if (nobleindex1 == nobles.size()) {
        cerr << "Attempting to battle with an unknown noble: " << noblename1 << endl;
    }
    //Checking if the warrior exsists
    else if (nobleindex2 == nobles.size()) {
        cerr << "Attempting to battle with an unknown noble: " << noblename2 << endl;
    }
    else { nobles[nobleindex1]->battle(*nobles[nobleindex2]); }
}

void displayStatus(const vector<Noble*> nobles, const vector<Warrior*> warriors) {
    cout << "Status\n=====\nNobles:" << endl; 
    for (const Noble* noble : nobles) {
        cout << *noble;
    }
    if (nobles.size() == 0) { 
        cout << "NONE" << endl;
    }
    cout << "\nUnemployed Warriors:" << endl;
    int counter = 0;
    for (const Warrior* warrior : warriors) {
        if (!warrior->isHired()) { 
            cout << *warrior; ++counter; 
        }
    }
    if (counter == 0) { 
        cout << "NONE" << endl; 
    }
}

void clearWar(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (Noble* noble : nobles) { delete noble; }
    nobles.clear();
    for (Warrior* warrior : warriors) { delete warrior; }
    warriors.clear();
}


