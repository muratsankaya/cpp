#include "Lord.h"
//#include "Noble.h"
#include "PersonWithStrengthToFight.h"
#include "Warrior.h"
using namespace std;
using namespace WarriorCraft;

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    /*Swordsman kenny("Kenny", 150);
    Wizard larry("Larry", 250);
    Swordsman ben(kenny);
    Lord dan("Daniel");
    sam.hires(kenny);*/
    sam.hires(samantha);
    /*dan.hires(kenny);
    sam.hires(larry);*/
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    /*PersonWithStrengthToFight ryan("Ryan the Young", 1000);
    cout << sam << randy;*/
    /*kenny.runaway();
    kenny.runaway();*/
    /*sam.fire(kenny);
    cout << sam;*/
    /*sam.battle(randy);
    joe.hires(samantha); */ //after the sam's battle samantha dies and I test it by trying to hire samantha
    joe.battle(randy);
    joe.battle(sam);
    //sam.battle(ryan);
    //samantha.runaway();
    //cout << sam;
    ////PWSTF battling lord
    ////randy.battle(joe); 
    ////PWSTF battles PWSTF
    //randy.battle(ryan);
    ////Checking for self battle
    //joe.battle(joe);
    //randy.battle(randy);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
