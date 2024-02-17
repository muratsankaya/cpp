#ifndef NOBLE_H
#define NOBLE_H
#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        virtual std::ostream& display(std::ostream& os) const = 0; 
        Noble(const std::string& name, double strength = 0);
        const std::string& getName() const;
        double getStrength() const;
        //I need this for lord's hire method
        bool isAlive() const;
        void battle(Noble& opponent);
        //Armies and Nobles will shout before entering the battle
        virtual void battleEnterance() const = 0;
    protected:
        //This is virtual because Lord's has to deal with warriors strengths
        virtual void setStrength(double weakerStrength);
        void updateStrength(double warriorStregth);
    private:
        std::string name;
        // I created a alive field because in the assignment it is stated that a Noble having 0 armyStrenght doesn't mean he/she is dead.
        bool alive;
        double strength;
        bool areAlive(const Noble& opponent) const;
    };
}
#endif
