//Jiayang Chen
//Lord.h
//Lords that can hire/fire protectors

#ifndef LORD

#define LORD

#include "Noble.h"
#include <vector>

namespace WarriorCraft {

    class Protector;

    class Lord : public Noble {
    public:
        
        Lord(const string& name);    
        
        //Hire a protector, adding a pointer of the protector to protectors
        //protector is not a const ref because we change the hired flag
        bool hire(Protector& protector);
        
        //Removes a protector from protectors
        bool remove(Protector* protector);
        
        //Fire a protector
        bool fire(Protector& protectors);
        
        void battlecry();
        
        void weaken(double multiplier);
        
    private:
        std::vector<Protector*> protectors;    
    }
}
#endif
