#include "Warrior.h"
#include "Noble.h"
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft {
    ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.warriors.size() << endl;
        for (const Warrior* warriorPtr : noble.warriors) {
            os << '\t' << *warriorPtr << endl;
        }
        return os;
    }

    Noble::Noble(const string& aName) : name(aName), isDead(false) {};

    //Hire a warrior, adding a pointer of the warrior to warriors
    //warrior is not a const ref because we change the hired flag    
    bool Noble::hire(Warrior& warrior) {
        //Do nothing if noble is already dead or warrior is hired
        if (isDead) {
            cerr << "noble " << name << " is dead!" << endl;
            return false;
        }
        if (warrior.isHired()) {
            cerr << "warrior " << warrior.getName() << " is already hired\n"; 
            return false;
        }
    
        warriors.push_back(&warrior);
        warrior.hiredBy(this);
        return true;
    }

    //Removes a warrior from warriors
    bool Noble::remove(Warrior* warrior) {
        //Find the index of the warrior to be removed
        size_t i = 0;
        //Keep looping until pointer matches
        while (i < warriors.size() && warriors[i] != warrior) {
            ++i;
        }
    
        //If i == size, that means the warrior was not found
        if (i == warriors.size()) {
            return false;
        }
    
        //To remove the warrior ptr from vector, shift everything down
        while (i < warriors.size() - 1) {
            warriors[i] = warriors[i+1];
        }
    
        //Remove the last element to save space
        warriors.pop_back();
        return true;
    
    }

    //Fire a warrior
    bool Noble::fire(Warrior& warrior) {
        if (isDead) {
            return false;
        }
        //Remove the warrior, check if it works also
        if (!remove(&warrior)) {
            cerr << "There is no such warrior " << warrior.getName() << " in "
                 << " noble " << name << "'s army" << endl;
            return false;
        }
    
        warrior.hiredBy(nullptr);
        cout << "You don't work for me anymore " << warrior.getName()
             << "! -- " << name << '.' << endl;
        return true;
    
    }

    //Battle another noble, using warriors in the order of hiring
    void Noble::battle(Noble& other) {
        cout << name << " battles " << other.name << endl;

        //Check for edge cases where at least one person is already dead
        if (isDead && other.isDead) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
            return;
        } else if (isDead) {
            cout << "He's dead, " << other.name << endl;
            return;
        } else if (other.isDead) {
            cout << "He's dead, " << name << endl;
            return;
        }

        double myStr = getStrength();
        double oStr = other.getStrength();
        //If this noble is stronger than the other
        if (myStr > oStr) {
            //Kill all the warriors in other
            for (Warrior* warrior : other.warriors) {
                warrior->setStrength(0);
            }
            other.isDead = true;
            //Damage own warriors
            for (Warrior* warrior : warriors) {
                //Take off the ratio
                double ratio = 1 - (oStr / myStr);
                warrior->setStrength(warrior->getStrength() * ratio);
            }
            //If other noble is stronger
        } else if (oStr > myStr) {
            //Kill all of own warriors
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
            isDead = true;
            //Damage other warriors
            for (Warrior* warrior : other.warriors) {
                //Take off the ratio
                double ratio = 1 - (myStr / oStr);
                warrior->setStrength(warrior->getStrength() * ratio);
            }
            //Else they tie
        } else {
            //Kill all warriors
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
            for (Warrior* warrior : other.warriors) {
                warrior->setStrength(0);
            }
            isDead = true;
            other.isDead = true;
        }

        
        if (isDead && other.isDead) {
            cout << "Mutual annihilation: " << name << " and "
                 << other.name << " die and each other's hands" << endl;
        }
        else if (isDead) {
            cout << other.name << " defeats " << name << endl;
        }
        else if (other.isDead) {
            cout << name << " defeats " << other.name << endl;
        }
    }


    //Returns the name
    const string& Noble::getName() const { return name; }

    //Sums the strength of all the warriors
    double Noble::getStrength() const {
        double str = 0;
        for (const Warrior* warrior : warriors) {
            str += warrior->getStrength();
        }
        return str;
    }
}
