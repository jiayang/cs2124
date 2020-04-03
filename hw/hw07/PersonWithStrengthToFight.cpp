#include "PersonWithStrengthToFight.h"
#include <string>
#include <iostream>
using namespace std;

namespace WarriorCraft {
    PersonWithStrengthToFight
    ::PersonWithStrengthToFight(const string& aName)
        :Noble(aName), strength(0) {}

    double PersonWithStrengthToFight::getStrength() const {
        return strength;
    }
    
    void PersonWithStrengthToFight::battlecry() const {
        cout << "UGH!!!\n";
    }
    
    void PersonWithStrengthToFight::weaken(double multiplier) {
        strength *= multiplier;
    }
}
