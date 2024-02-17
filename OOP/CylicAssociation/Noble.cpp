

#include <iostream>;
#include <string>;
#include <vector>;
#include "Noble.h";
#include "Warrior.h";
using namespace std;

namespace WarriorCraft {
    ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (const Warrior* warriorptr : noble.army) {
            os << *warriorptr;
        }
        return os;
    }

    Noble::Noble(const string& name) : name(name), isAlive(true), armyStrength(0) {};

    const string& Noble::getName() const { return name; }

    void Noble::battle(Noble& opponent) { // How can I make this shorter ?
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

    bool Noble::hire(Warrior& warrior) {
        if (isAlive) {
            if (warrior.isHired()) {
                cout << warrior.getName() << " already fights for another Noble! " << endl;
                return false;
            }
            else {
                army.push_back(&warrior);
                updateArmyStrenght(warrior.getStrength());
                warrior.setHire(this); //This will mark that the warrior is hired
                return true;
            }
        }
        else { cout << name << " is dead, he can not hire a warrior!" << endl; return false; }
    }

    bool Noble::fire(Warrior& warrior) {
        if (isAlive) {
            size_t warriorIndex = findWarrior(warrior.getName());

            //The warrior may not be in the Noble's amry
            if (warriorIndex == army.size()) {
                cout << warrior.getName() << " does not fight for " << name << '!' << endl; return false;
            }
            else {
                cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << '.' << endl;
                this->remove(warriorIndex);

                //I'm passing the warrior strenght as a negative value
                updateArmyStrenght(-warrior.getStrength());
                warrior.setFree();
                return true;
            }
        }
        else { cout << name << " is dead, he can not fire a warrior!" << endl; return false; }
    }
    //I need this function for the warrior to run away
    void Noble::removeWarrior(const string& warriorName) {
        size_t warriorIndex = findWarrior(warriorName);
        updateArmyStrenght(-army[warriorIndex]->getStrength()); //I'm again passing it as a negative double val
        remove(warriorIndex);
    }

    //I will keep the weakerstrength on the rhs 
    void Noble::setStrength(double& weakerStrength) {
        armyStrength -= weakerStrength;
        weakerStrength = 0;
    }

    void Noble::setWarriorsStrength(double fraction) {
        for (Warrior* warrior : army) {
            warrior->setStrenght(fraction);
        }
    }

    size_t Noble::findWarrior(const string& name) const {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i]->getName() == name) {
                return i;
            }
        }
        return army.size();
    }

    void Noble::updateArmyStrenght(double warriorStrenght) {
        armyStrength += warriorStrenght;
    }

    bool Noble::areAlive(const Noble& opponent) const {
        if (!opponent.isAlive && !isAlive) { cout << "Oh, NO! They're both dead! Yuck!" << endl; return false; }
        else if (!opponent.isAlive) { cout << "He's dead, " << name << endl; return false; }
        else if (!isAlive) { cout << "He's dead, " << opponent.name << endl; return false; }
        return true;
    }

    void Noble::remove(size_t index) {
        for (size_t i = index; i != army.size() - 1; ++i) {
            army[i] = army[i + 1];
        }
        army.pop_back();
    }
}