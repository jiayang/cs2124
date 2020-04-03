#include "Archer.h"
#include "Protector.h"
#include "Lord.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    void Archer::battlecry() const {
        cout << "TWANG! " << getName()
             << " says: Take that in the name of my lord, "
             << getLord()->getName() << "\n";
    }
}
