#include "Noble.h"
#include "Protector.h"
#include "Lord.h"
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft {

    Lord::Lord(const string& name) :Noble(name) {}

    //Hire a protector, adding a pointer of the protector to protectors
    //protector is not a const ref because we change the hired flag    
    bool Lord::hires(Protector& protector) {
        //Do nothing if lord is already dead or protector is hired
        if (isDead()) {
            //cerr << "noble " << getName() << " is dead!" << endl;
            return false;
        }
        if (protector.isHired()) {
            cerr << "protector " << protector.getName()
                 << " is already hired\n"; 
            return false;
        }
    
        protectors.push_back(&protector);
        protector.hiredBy(this);
        return true;
    }

    const string& Lord::getName() const {
        return this->Noble::getName();
    }
    
    //Removes a protector from protectors
    bool Lord::remove(Protector* protector) {
        //Find the index of the protector to be removed
        size_t i = 0;
        //Keep looping until pointer matches
        while (i < protectors.size() && protectors[i] != protector) {
            ++i;
        }
    
        //If i == size, that means the protector was not found
        if (i == protectors.size()) {
            return false;
        }
    
        //To remove the protector ptr from vector, shift everything down
        while (i < protectors.size() - 1) {
            protectors[i] = protectors[i+1];
        }
    
        //Remove the last element to save space
        protectors.pop_back();
        return true;
    
    }

    //Fire a protector
    bool Lord::fire(Protector& protector) {
        if (isDead()) {
            return false;
        }
        //Remove the protector, check if it works also
        if (!remove(&protector)) {
            cerr << "There is no such protector " << protector.getName()
                 << " in "
                 << " lord " << getName() << "'s army" << endl;
            return false;
        }
    
        protector.hiredBy(nullptr);
        cout << "You don't work for me anymore " << protector.getName()
             << "! -- " << getName() << '.' << endl;
        return true;
    
    }

    //Multiply every lord's strength by the ratio
    void Lord::weaken(double ratio) {
        for (Protector* protector : protectors) {
            protector->setStrength(protector->getStrength() * ratio);
        }
        if (ratio == 0) {
            setIsDead(true);
        }
    }

    //Battlecry by calling protector battlecrys
    void Lord::battlecry() const {
        for (const Protector* protector : protectors) {
            if (protector->getStrength() > 0) {
                protector->battlecry();
            }
        }
    }
    
    
    //Sums the strength of all the lords
    double Lord::getStrength() const {
        double str = 0;
        for (const Protector* protector : protectors) {
            str += protector->getStrength();
        }
        return str;
    }
}
