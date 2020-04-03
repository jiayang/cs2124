#include "Protector.h"
#include "Lord.h"
#include <string>
#include <ostream>
#include <vector>
using namespace std;

namespace WarriorCraft {

    Protector::Protector(const string& aName, double aStrength)
        : name(aName), strength(aStrength), lord(nullptr) {};

    //Returns whether or not the warrior is hired
    bool Protector::isHired() const {return lord != nullptr;}

    //Sets the lord owner
    void Protector::hiredBy(Lord* owner) {lord = owner;}

    //Runs away from the lord
    bool Protector::runaway() {
        //If there is no owner
        if (lord == nullptr) {
            cerr << "No owner" << endl;
            return false;
        }
        lord->remove(this);
        cout << name << " flees in terror, abandoning his lord, "
             << lord->getName() << endl;
        lord = nullptr;
    }

    //Returns the name of the warrior
    const string& Protector::getName() const {return name;}

    //Set strength
    void Protector::setStrength(double str) {strength = str;}

    //Returns the strength
    double Protector::getStrength() const {return strength;}

    Lord* const Protector::getLord() const {return lord;}
}
