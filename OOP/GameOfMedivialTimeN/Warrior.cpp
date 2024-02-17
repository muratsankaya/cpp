#include "Warrior.h"
#include "Lord.h"
using namespace std;

namespace WarriorCraft {
    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << '\t' << warrior.name << ": " << warrior.strength << endl;
        return os;
    }

    Warrior::Warrior(const string& name, double strength) : name(name),
        strength(strength), hired(false), boss(nullptr) {};

    const string& Warrior::getName() const { return name; }

    double Warrior::getStrength() const { return strength; }

    const string& Warrior::getLordName() const { return boss->getName(); }

    //I can't pass the pointer as a const here becuase, because I will have to make changes on the Lord if the warrior runs away
    void Warrior::setHire(Lord* nobleptr) { hired = true;  boss = nobleptr; }

    void Warrior::setFree() { hired = false; boss = nullptr; }

    void Warrior::setStrenght(double newStrenghtFraction) {
        strength *= newStrenghtFraction;
    }

    //To check if the warrior is employed
    bool Warrior::isHired() const { return hired; }

    bool Warrior::runaway() {
        if (boss != nullptr) {
            if (strength == 0) { cerr << name << " is dead!" << endl; return false; }
            cout << name << " flees in terror, abonding his lord, " << boss->getName() << endl;
            boss->removeWarrior(this); //I'm removing the warrior from the Noble's army
            setFree();
            return true;
        }
        cerr << name << " is not hired by a Noble!" << endl; return false;
    }

    void Warrior::shout() const {
        cout << name << " says: "
            << "Take that in the name of my lord, "
            << getLordName() << endl;
    }

    Archer::Archer(const string& name, double strength) : Warrior(name, strength) {}

    void Archer::shout() const { cout << "TWANG!  "; Warrior::shout(); }

    Swordsman::Swordsman(const string& name, double strength) : Warrior(name, strength) {}

    void Swordsman::shout() const { cout << "CLANG!  "; Warrior::shout(); }

    Wizard::Wizard(const string& name, double strength) : Warrior(name, strength) {}

    void Wizard::shout() const { cout << "POOF!\n"; }
}