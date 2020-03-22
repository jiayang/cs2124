//Jiayang Chen
//Noble that can hire,fire warriors and battle other nobles
//Noble.h

#ifndef NOBLE

#define NOBLE

#include <vector>
#include <string>
#include <iostream>

namespace WarriorCraft {
    
    class Warrior;
    
    //A noble class who has a name and a vector of warriors
    //Also has a bool for whether or not they are dead
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        Noble(const std::string& aName);
        
        //Hire a warrior, adding a pointer of the warrior to warriors
        //warrior is not a const ref because we change the hired flag
        bool hire(Warrior& warrior);
        
        //Removes a warrior from warriors
        bool remove(Warrior* warrior);
        
        //Fire a warrior
        bool fire(Warrior& warrior);
        
        //Battle another noble, using warriors in the order of hiring
        void battle(Noble& other);
        
        //Returns the name
        const std::string& getName() const;
        
        //Sums the strength of all the warriors
        double getStrength() const;

    private:
        std::string name;
        std::vector<Warrior*> warriors;
        bool isDead;
        
    };
}
#endif
    
