#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>;
#include <string>;
#include <vector>;

namespace WarriorCraft {
    class Warrior;
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        Noble(const std::string& name);
        const std::string& getName() const;
        void battle(Noble& opponent);
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        void removeWarrior(const std::string& warriorName);
    private:
        std::vector<Warrior*> army;
        std::string name;
        double armyStrength;
        // I created a isAlive field because in the assignment it is stated that a Noble having 0 armyStrenght doesn't mean he/she is dead.
        bool isAlive;
        //I will keep the weakerstrength on the rhs 
        void setStrength(double& weakerStrength);
        void setWarriorsStrength(double fraction);
        size_t findWarrior(const std::string& name) const;
        void updateArmyStrenght(double warriorStrenght);
        bool areAlive(const Noble& opponent) const;
        void remove(size_t index);
    };
}

#endif

