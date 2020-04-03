#ifndef WIZARD

#define WIZARD

#include "Protector.h"

namespace WarriorCraft {
    class Wizard : public Protector {
        using Protector::Protector;

        void battlecry() const;
    }

}

#endif
