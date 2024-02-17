#ifndef PERSONWITHSTRENGTHTOFIGHT
#define PERSONWITHSTRENGTHTOFIGHT
#include "Noble.h"

namespace WarriorCraft {
    class PersonWithStrengthToFight : public Noble {
    public:
        std::ostream& display(std::ostream& os) const override;
        PersonWithStrengthToFight(const std::string& name, double strength);
        void battleEnterance() const override;
    };
}

#endif
