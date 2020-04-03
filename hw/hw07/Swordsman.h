#ifndef SWORDSMAN

#define SWORDSMAN

#include "Protector.h"

namespace WarriorCraft {
    class Swordsman : public Protector {
        using Protector::Protector;

        void battlecry() const;
    };

}

#endif
