#include "Lord.h"
#include "Warrior.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    ostream& Lord::display(ostream& os) const {
        os << getName() << " has an army of " << army.size() << endl;
        for (const Warrior* warriorptr : army) {
            os << *warriorptr;
        }
        return os;
    }

    Lord::Lord(const string& name) : Noble(name) {}

    void Lord::battleEnterance() const {
        for (const Warrior* warriorptr : army) { warriorptr->shout(); }
    }

    //I will keep the weaker strength on the rhs
    void Lord::setStrength(double weakerStrength) { //I had to override this method for the lord because they have protectors
        setWarriorsStrength(1 - (weakerStrength / getStrength())); //The only difference is for lord I also have to set the warriors strengths
        Noble::setStrength(weakerStrength);
    }

    void Lord::setWarriorsStrength(double fraction) {
        //if the fraction is == 1, that means the the curr object has the weaker strength and the warriors will die
        if (fraction == 1) fraction = 0;
        for (Warrior* warrior : army) {
            warrior->setStrenght(fraction);
        }
    }

    bool Lord::hires(Warrior& warrior) {
        if (isAlive()) {
            if (warrior.isHired()) { //Since a dead warrior can not be fired nor runaway, this will disable a dead warrior from getting hired
                cout << warrior.getName() <<
                    " already fights for another Noble! " << endl;
                return false;
            }
            else {
                army.push_back(&warrior);
                updateStrength(warrior.getStrength());
                warrior.setHire(this); //This will mark that the warrior is hired, and will associate the warrior with the curr lord
                return true;
            }
        }
        else { cout << getName() << " is dead, he can not hire a warrior!" << endl; return false; }
    }

    bool Lord::fire(Warrior& warrior) {
        if (isAlive()) {
            size_t warriorIndex = findWarrior(&warrior);
            //The warrior may not be in the Noble's amry
            if (warriorIndex == army.size()) {
                cout << warrior.getName() << " does not fight for " << getName() << '!' << endl;
                return false;
            }
            else {
                cout << "You don't work for me anymore " << warrior.getName()
                    << "! -- " << getName() << '.' << endl;
                remove(warriorIndex);
                //I'm passing the warrior strength as a negative value
                updateStrength(-warrior.getStrength());
                warrior.setFree();
                return true;
            }
        }
        else { cout << getName() << " is dead, he can not fire a warrior!" << endl; return false; }
    }

    size_t Lord::findWarrior(const Warrior* warriorptr) const {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == warriorptr) {
                return i;
            }
        }
        return army.size(); // I need this for the fire method
    }

    void Lord::removeWarrior(const Warrior* ptr) { //I'm making sure the warrior is in the army before executing this function 
        size_t warriorIndex = findWarrior(ptr);
        updateStrength(-army[warriorIndex]->getStrength()); //I'm again passing it as a negative double val
        remove(warriorIndex);
    }

    void Lord::remove(size_t index) {
        for (size_t i = index; i != army.size() - 1; ++i) {
            army[i] = army[i + 1];
        }
        army.pop_back();
    }
}