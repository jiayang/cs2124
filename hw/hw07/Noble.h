//Jiayang Chen
//Noble abstract class that can battle
//Noble.h

#ifndef NOBLE

#define NOBLE

#include <vector>
#include <string>
#include <iostream>

namespace WarriorCraft {
   
    //A noble class who has a name and a vector of protectors
    //Also has a bool for whether or not they are dead
    class Noble {
    public:
        Noble(const std::string& aName);
        
        //Battle another noble
        void battle(Noble& other);
        
        //Returns the name
        const std::string& getName() const;
        
        virtual double getStrength() const = 0;

        //Battlecry
        virtual void battlecry() const = 0;

        //Either weaken the noble or its warriors
        virtual void weaken(double multiplier) = 0;

        bool isDead() const;

        void setIsDead(bool dead);
    private:
        std::string name;
        bool amIDead;
    };
}
#endif
    
