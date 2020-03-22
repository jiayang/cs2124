//Jiayang Chen
//Warrior that has a strength, can battle, and has a Noble owner
//Warrior.h

#ifndef WARRIOR
#define WARRIOR

#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
    class Noble;
    
    //A warrior class that has a name and a strength
    //Also knows his/her owner (if there is one)
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
        
    public:
        Warrior(const std::string& aName, double aStrength);
        
        //Returns whether or not the warrior is hired
        bool isHired() const;
        
        //Sets the noble owner
        void hiredBy(Noble* owner);
        
        //Runs away from the noble
        bool runaway();
        
        //Returns the name of the warrior
        const std::string& getName() const;
    
        //Set strength
        void setStrength(double str);

        //Returns the strength
        double getStrength() const;
    
    private:
        std::string name;
        double strength;
        Noble* noble;
    };
}
#endif
