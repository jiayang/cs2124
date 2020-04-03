//Jiayang Chen
//Lord.h
//Lords that can hire/fire protectors

#ifndef LORD

#define LORD

#include "Noble.h"
#include <vector>
#include <string>

namespace WarriorCraft {

    class Protector;

    class Lord : public Noble {
    public:
        
        Lord(const std::string& name);    
        
        //Hire a protector, adding a pointer of the protector to protectors
        //protector is not a const ref because we change the hired flag
        bool hires(Protector& protector);
        
        //Removes a protector from protectors
        bool remove(Protector* protector);
        
        //Fire a protector
        bool fire(Protector& protectors);
        
        void battlecry() const;
        
        void weaken(double multiplier);
        
        double getStrength() const;

        const std::string& getName() const;
    private:
        std::vector<Protector*> protectors;    
    };
}
#endif
