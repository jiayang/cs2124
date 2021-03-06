#include "Noble.h"
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& aName) : name(aName), amIDead(false) {};

    //Battle another noble, using warriors in the order of hiring
    void Noble::battle(Noble& other) {
        cout << name << " battles " << other.name << endl;
        battlecry();
        other.battlecry();

        //Check for edge cases where at least one person is already dead
        if (amIDead && other.amIDead) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
            return;
        } else if (amIDead) {
            cout << "He's dead, " << other.name << endl;
            return;
        } else if (other.amIDead) {
            cout << "He's dead, " << name << endl;
            return;
        }

        double myStr = getStrength();
        double oStr = other.getStrength();
        //If this noble is stronger than the other
        if (myStr > oStr) {
            double ratio = 1 - oStr/myStr;
            weaken(ratio); //Weaken own nobles
            other.weaken(0); //Kill off the other noble
            
        //If other noble is stronger
        } else if (oStr > myStr) {
            double ratio = 1 - myStr/oStr;
            other.weaken(ratio);
            weaken(0);
            
        //Else they tie
        } else {
            weaken(0);
            other.weaken(0);
        }

        
        if (amIDead && other.amIDead) {
            cout << "Mutual annihilation: " << name << " and "
                 << other.name << " die and each other's hands" << endl;
        }
        else if (amIDead) {
            cout << other.name << " defeats " << name << endl;
        }
        else if (other.amIDead) {
            cout << name << " defeats " << other.name << endl;
        }
    }


    //Returns the name
    const string& Noble::getName() const { return name; }

    //Returns if dead
    bool Noble::isDead() const {return amIDead;}

    void Noble::setIsDead(bool dead) {
        amIDead = dead;
    }
}
