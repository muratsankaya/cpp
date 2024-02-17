
/*
  hw04.cpp
  Spring 2022
  Association: Noble - Warrior
  Murat Sankaya
 */

#include <iostream>
#include <vector>
#include <string>
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
   
    void fire(Warrior& warrior) {
        if (isAlive) {
            size_t warriorIndex = findWarrior(warrior.getName());

            //The warrior may not be in the Noble's amry
            if (warriorIndex == army.size()) {
                cout << warrior.getName() << " does not fight for " << name << '!' << endl;
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
            }
        }
        else{ cout << name << " is dead, he can not fire a warrior!" << endl; }
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
    os <<'\t' << warrior.name << ": " << warrior.strength << endl;
    return os;
}

ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.army.size() << endl;
    for (const Warrior* warriorptr : noble.army) {
        os << *warriorptr;
    }
    return os;
}

int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    //lance.battle(jim);
    art.hire(wizard);
    lance.hire(dylan);
    //linus.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << "==========\n"
        << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    /*art.fire(mrGreen);*/
    cout << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    linus.battle(billie);
    billie.battle(lance);
    /*billie.battle(linus);
    billie.battle(art);
    billie.fire(cheetah);
    billie.hire(cheetah);
    linus.hire(mrGreen);
    linus.battle(linus);*/
    cout << "==========\n"
        << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}
