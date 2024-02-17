#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>;
#include <iostream>;

namespace WarriorCraft {
    class Noble;
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
    public:
        Warrior(const std::string& name, double strength);
        const std::string& getName() const;
        double getStrength() const;
        void setHire(Noble* nobleptr);
        void setFree();
        //To check if the warrior is employed
        bool isHired() const;
        void setStrenght(double newStrenghtFraction);
        bool runaway();
    private:
        std::string name;
        double strength;
        bool hired;    //Either employed or free 
        Noble* boss;
    };
}

#endif

