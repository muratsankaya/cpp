#ifndef LORD_H
#define LORD_H
#include <vector>
#include "Noble.h"

namespace WarriorCraft {
    class Warrior;
    class Lord : public Noble {
    public:
        std::ostream& display(std::ostream& os) const override;
        Lord(const std::string& name);
        void setStrength(double weakerStrength) override;
        void battleEnterance() const override;
        bool hires(Warrior& warrior);
        bool fire(Warrior& warrior);
        void removeWarrior(const Warrior* ptr); //Warrior class calls this method it can not be private
    private:
        std::vector<Warrior*> army;
        void setWarriorsStrength(double fraction);
        void remove(size_t index);
        size_t findWarrior(const Warrior* warriorptr) const;
    };
}
#endif
