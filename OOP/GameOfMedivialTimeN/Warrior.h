#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>
#include <iostream>

namespace WarriorCraft {
    class Lord;
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
    public:
        Warrior(const std::string& name, double strength);
        const std::string& getName() const;
        double getStrength() const;
        const std::string& getLordName() const;
        //To check if the warrior is employed
        bool isHired() const;
        //Can not be a const Lord* because at runaway I call the removeWarrior method of the lord which is not const
        void setHire(Lord* lordptr); //I needed this to be a lord pointer instead of Noble, because I call the removeWarrior() method which only exsists for Lord
        void setFree();
        void setStrenght(double newStrenghtFraction);
        bool runaway();
        virtual void shout() const = 0;
    private:
        std::string name;
        double strength;
        bool hired;    //Either employed or free 
        Lord* boss;
    };
    class Archer : public Warrior {
    public:
        Archer(const std::string& name, double strength);
        void shout() const override;
    };
    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string& name, double strength);
        void shout() const override;
    };
    class Wizard : public Warrior {
    public:
        Wizard(const std::string& name, double strenght);
        void shout() const override;
    };
}
#endif