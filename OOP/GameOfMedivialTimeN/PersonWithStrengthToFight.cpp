#include "PersonWithStrengthToFight.h"
using namespace std;

namespace WarriorCraft {
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name,
        double strength) : Noble(name, strength) {}

    void PersonWithStrengthToFight::battleEnterance() const {
        cout << "Ugh !\n";
    }

    ostream& PersonWithStrengthToFight::display(ostream& os) const {
        os << getName() << " is an alone fighter!\n"; return os;
    }
}