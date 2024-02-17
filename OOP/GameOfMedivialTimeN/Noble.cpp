#include "Noble.h"
using namespace std;

namespace WarriorCraft {
    ostream& operator<<(ostream& os, const Noble& rhs) {
        rhs.display(os);
        return os;
    }
    
    Noble::Noble(const string& name, double strength) : name(name), strength(strength), alive(true) {};

    const string& Noble::getName() const { return name; }

    double Noble::getStrength() const { return strength; }

    //I will keep the weaker strength on the rhs
    void Noble::setStrength(double weakerStrength) {
        if (weakerStrength == 0) {
            strength = 0;
            alive = false;
        }
        else strength -= weakerStrength;
    }

    // Two different types of nobles will be able to battle each other
    void Noble::battle(Noble& opponent) {
        if (this != &opponent) {
            cout << name << " battles " << opponent.name << endl;
            if (areAlive(opponent)) {
                if (strength > opponent.strength) {
                    setStrength(opponent.strength);
                    opponent.setStrength(0);
                    cout << name << " defeats " << opponent.name << endl;
                }
                else if (strength == opponent.strength) {
                    setStrength(0);
                    opponent.setStrength(0);
                    cout << "Mutual Annihilation: " << name <<
                        " and " << opponent.name <<
                        " die at each other's hands." << endl;
                }
                else {
                    opponent.setStrength(strength);
                    setStrength(0);
                    cout << opponent.name << " defeats " << name << endl;
                }
            }
        }
        else cerr << name << " will not fight himself!\n";
    }

    void Noble::updateStrength(double warriorStrength) { strength += warriorStrength; }

    //I need to check the alive field for some of the Lord's methods
    bool Noble::isAlive() const { return alive; }

    bool Noble::areAlive(const Noble& opponent) const {
        if (!opponent.alive && !alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl; return false;
        }
        else if (!opponent.alive) {
            battleEnterance();
            cout << "He's dead, " << name << endl; return false;
        }
        else if (!alive) {
            opponent.battleEnterance();
            cout << "He's dead, " << opponent.name << endl; return false;
        }
        battleEnterance(); opponent.battleEnterance();
        return true;
    }
}