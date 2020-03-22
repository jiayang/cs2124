#include "Warrior.h"
#include "Noble.h"
#include <string>
#include <ostream>
#include <vector>
using namespace std;

namespace WarriorCraft {
    
    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }

    Warrior::Warrior(const string& aName, double aStrength)
        : name(aName), strength(aStrength), noble(nullptr) {};

    //Returns whether or not the warrior is hired
    bool Warrior::isHired() const {return noble != nullptr;}

    //Sets the noble owner
    void Warrior::hiredBy(Noble* owner) {noble = owner;}

    //Runs away from the noble
    bool Warrior::runaway() {
        //If there is no owner
        if (noble == nullptr) {
            cerr << "No owner" << endl;
            return false;
        }
        noble->remove(this);
        cout << name << " flees in terror, abandoning his lord, "
             << noble->getName() << endl;
        noble = nullptr;
    }

    //Returns the name of the warrior
    const string& Warrior::getName() const {return name;}

    //Set strength
    void Warrior::setStrength(double str) {strength = str;}

    //Returns the strength
    double Warrior::getStrength() const {return strength;}

}
