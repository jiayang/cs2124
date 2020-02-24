//Jiayang Chen
//Creating nobles who hire and fire warriors
//hw04.cpp

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//A warrior class that has a name and a strength
//Also knows if they are hired or not
class Warrior {
public:
    Warrior(const string& aName, int aStrength)
        : name(aName), strength(aStrength), hired(false) {};

    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
    
    //Returns whether or not the warrior is hired
    bool isHired() const {return hired;}

    //Set hired true or false
    void setHired(bool hire) {hired = hire;}

    //Returns the name of the warrior
    string getName() const {return name;}

    //Set strength
    void setStrength(int str) {strength = str;}

    //Returns the strength
    int getStrength() const {return strength;}
    
private:
    string name;
    int strength;
    bool hired;
};

//A noble class who has a name and a vector of warriors
//Also has a bool for whether or not they are dead
class Noble {
public:
    Noble(const string& aName) : name(aName), isDead(false) {};

    friend ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.warriors.size() << endl;
        for (Warrior* warriorPtr : noble.warriors) {
            os << '\t' << *warriorPtr << endl;
        }
        return os;
    }
    
    //Hire a warrior, adding a pointer of the warrior to warriors
    //warrior is not a const ref because we change the hired flag
    bool hire(Warrior& warrior) {
        //Do nothing if noble is already dead or warrior is hired
        if (isDead || warrior.isHired()) { 
            return false;
        }

        warriors.push_back(&warrior);
        warrior.setHired(true);
        return true;
    }

    //Fire a warrior
    bool fire(Warrior& warrior) {
        if (isDead) {
            return false;
        }
        //Find the index of the warrior to be fired
        size_t i = 0;
        //Keep looping until pointer is the address of warrior
        while (i < warriors.size() && warriors[i] != &warrior) {
            ++i;
        }

        //If i == size, that means the warrior was not found
        if (i == warriors.size()) {return false;}

        //To remove the warrior ptr from vector, shift everything down
        while (i < warriors.size() - 1) {
            warriors[i] = warriors[i+1];
        }

        //Remove the last element to save space
        warriors.pop_back();

        warrior.setHired(false);
        cout << "You don't work for me anymore " << warrior.getName()
             << "! -- " << name << '.' << endl;
        return true;

    }

    //Battle another noble, using warriors in the order of hiring
    void battle(Noble& other) {
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

        //Indexes for current warrior 1 and 2
        size_t i = 0;
        size_t j = 0;

        //Keep looping until i or j reaches the end
        //i.e one noble is out of warriors
        while (i < warriors.size() && j < other.warriors.size()) {
            Warrior& war1 = *(warriors[i]);
            Warrior& war2 = *(other.warriors[j]);
            int str1 = war1.getStrength();
            int str2 = war2.getStrength();
             
            if (str1 > str2) {
                war1.setStrength(str1 - str2);
                war2.setStrength(0);
                ++j;
            } else if (str1 == str2) {
                war1.setStrength(0);
                war2.setStrength(0);
                ++i;
                ++j;
            } else {
                war2.setStrength(str2 - str1);
                war1.setStrength(0);
                ++i;
            }
            
            
        }
        //After all the battling is done,
        //if i is at the end, noble1 is dead
        //if j is at the end, noble2 is dead
        isDead = i == warriors.size();
        other.isDead = j == other.warriors.size();
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
    
private:
    string name;
    vector<Warrior*> warriors;
    bool isDead;
};


int main() {
    Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");
	
	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);
	
	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
    art.hire(cheetah);

    cout << "==========\n"
         << "Status before all battles, etc.\n";
	cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
	cout << art << endl;
    art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
	cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
    cout << "==========\n";
	
}


    
// 15

// 12 3


// str1 = 15
// str2 = 12
