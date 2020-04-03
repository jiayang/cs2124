//Jiayang Chen
//Protector that has a strength, can battle, and has a lord
//Protector.h

#ifndef PROTECTOR
#define PROTECTOR

#include <string>

namespace WarriorCraft {
    class Lord;
    
    //A protector class that has a name and a strength
    //Also knows his/her owner (if there is one)
    class Protector {
    public:
        Protector(const std::string& aName, double aStrength);
        
        //Returns whether or not the protector is hired
        bool isHired() const;
        
        //Sets the lord owner
        void hiredBy(Lord* owner);
        
        //Runs away from the lord
        bool runaway();
        
        //Returns the name of the Protector
        const std::string& getName() const;
    
        //Set strength
        void setStrength(double str);

        //Returns the strength
        double getStrength() const;

        virtual void battlecry() const = 0;

        Lord* const getLord() const;
    private:
        std::string name;
        double strength;
        Lord* lord;
    };
}
#endif
