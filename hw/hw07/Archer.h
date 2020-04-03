#ifndef ARCHER

#define ARCHER

#include "Protector.h"

namespace WarriorCraft {
    class Archer : public Protector {
        using Protector::Protector;

        void battlecry() const;
    };

}

#endif
