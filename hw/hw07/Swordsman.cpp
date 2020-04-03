#include "Swordsman.h"
#include "Protector.h"
#include "Lord.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    void Swordsman::battlecry() const {
        cout << "CLANG! " << getName()
             << " says: Take that in the name of my lord, "
             << getLord()->getName() << "\n";
    }
}
