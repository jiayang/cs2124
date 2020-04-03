#include "PersonWithStrengthToFight.h"
#include <string>
#include <iostream>
using namespace std;

namespace WarriorCraft {
    PersonWithStrengthToFight
    ::PersonWithStrengthToFight(const string& aName, int strength)
        :Noble(aName), strength(strength) {}

    double PersonWithStrengthToFight::getStrength() const {
        return strength;
    }
    
    void PersonWithStrengthToFight::battlecry() const {
        if (isDead()) { return;}
        cout << "UGH!!!\n";
    }
    
    void PersonWithStrengthToFight::weaken(double multiplier) {
        strength *= multiplier;
        if (multiplier == 0) {
            setIsDead(true);
        }
    }
}
