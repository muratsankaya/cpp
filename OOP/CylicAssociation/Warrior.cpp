

#include <iostream>;
#include <string>;
#include "Noble.h";
#include "Warrior.h";
using namespace std;

namespace WarriorCraft {

    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << '\t' << warrior.name << ": " << warrior.strength << endl;
        return os;
    }

    Warrior::Warrior(const string& name, double strength) : name(name), strength(strength),
        hired(false), boss(nullptr) {};

    const string& Warrior::getName() const { return name; }

    double Warrior::getStrength() const { return strength; }

    // I can't pass the pointer as a const here becuase, because I will have to make changes on the Noble if the warrior runs away
    void Warrior::setHire(Noble* nobleptr) { hired = true; boss = nobleptr; }

    void Warrior::setFree() { hired = false; boss = nullptr; }

    //To check if the warrior is employed
    bool Warrior::isHired() const { return hired; }

    void Warrior::setStrenght(double newStrenghtFraction) {
        strength *= newStrenghtFraction;
    }

    bool Warrior::runaway() {
        if (boss != nullptr) {
            if (strength == 0) { cerr << name << " is dead!" << endl; return false; }
            cout << name << " flees in terror, abonding his lord, " << boss->getName() << endl;
            boss->removeWarrior(name); //I'm removing the warrior from the Noble's army
            this->setFree();
            return true;
        }
        cerr << name << " is not hired by a Noble!" << endl; return false;
    }

}
