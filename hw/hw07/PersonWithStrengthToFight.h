//Jiayang Chen
//Person with strength to fight other nobles
//PersonWithStrengthToFight.h

#ifndef STRONGPERSON

#define STRONGPERSON

#include "Noble.h"
#include <string>

namespace WarriorCraft {
   
    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& aName);

        double getStrength() const;

        void battlecry() const;

        void weaken(double multiplier);
        
    private:
        double strength;
    };
}
#endif
    
