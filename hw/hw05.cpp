//Jiayang Chen
//Creating nobles who hire and fire warriors **DYNAMICALLY**!
//hw05.cpp

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
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

            //Determine which warrior wins the specific battle
            //"Kill" the losing warrior by setting str to 0
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

    //Returns the name
    string getName() const { return name; }
    
private:
    string name;
    vector<Warrior*> warriors;
    bool isDead;
};

//Find noble given the vector of nobles
size_t findNoble(const vector<Noble*>& nobles, const string& name) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == name) {
            return i;
        }
    }
    return nobles.size();
}

//Finds a warrior from a vector given a name
size_t findWarrior(const vector<Warrior*>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getName() == name) {
            return i;
        }
    }
    return warriors.size();
}


//Creates a warrior from the stream and adds it to the vector of warriors
void addWarrior(ifstream& commands, vector<Warrior*>& warriors) {
    string name;
    int str;
    commands >> name >> str;
    Warrior* newWarrior = new Warrior(name,str);
    warriors.push_back(newWarrior);
}

//Creates a warrior from the stream and adds it to the vector of warriors
void addNoble(ifstream& commands, vector<Noble*>& nobles) {
    string name;
    commands >> name;
    Noble* newNoble = new Noble(name);
    nobles.push_back(newNoble);
}
//Prints the status of all the warriors
void status(const vector<Warrior*>& warriors) {
    cout << "There are " << warriors.size() << " warriors." << endl;
    for (Warrior* warrior : warriors) {
        cout << *warrior << endl;
    }
}

//Initiates a battle between two nobles
void battle(ifstream& commands, vector<Noble*>& nobles) {
    string name1,name2;
    commands >> name1 >> name2;
    //Find the index of the nobles
    size_t index1 = findNoble(nobles, name1);
    size_t index2 = findNoble(nobles, name2);

    //If either of the indexes is nobles.size() (couldn't find), print error
    if (index1 == nobles.size() || index2 == nobles.size()) {
        cerr << "Can not find one of the nobles to fight!" << endl;
        return;
    }
    
    nobles[index1]->battle(*nobles[index2]);
}


//Hire a warrior to a noble using command stream
void hire(ifstream& commands, vector<Noble*>& nobles,
          vector<Warrior*>& warriors) {
    string nobleName, warriorName;
    commands >> nobleName >> warriorName;
    size_t nobleI = findNoble(nobles, nobleName);
    size_t warriorI = findWarrior(warriors, warriorName);

    nobles[nobleI]->hire(*warriors[warriorI]);
}


//Fire a warrior to a noble using command stream
void fire(ifstream& commands, vector<Noble*>& nobles,
          vector<Warrior*>& warriors) {
    string nobleName, warriorName;
    commands >> nobleName >> warriorName;
    size_t nobleI = findNoble(nobles, nobleName);
    size_t warriorI = findWarrior(warriors, warriorName);

    nobles[nobleI]->fire(*warriors[warriorI]);
}

//Prints the status of all the nobles and warriors
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) {
    //Print all the nobles and their warriors
    for (const Noble* noble : nobles) {
        cout << *noble << endl;
    }
    //Print all the warriors that were not printed (not hired)
    for (const Warrior* warrior : warriors) {
        if (!(warrior->isHired())) {
            cout << *warrior << endl;
        }
    }
}

//Clear all the warriors
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (Warrior*& warrior : warriors) {
        delete warrior;
        warrior = nullptr;
    }
    for (Noble*& noble : nobles) {
        delete noble;
        noble = nullptr;
    }

}

int main() {
    ifstream commands("nobleWarriors.txt");
    if (!commands) {
        cerr << "Could not open nobleWarriors.txt" << endl;
        exit(1);
    }

    vector<Warrior*> warriors; //Vector of warriors
    vector<Noble*> nobles; // all the nobles
    
    string command;
    //While there are still commands to execute
    while (commands >> command) {
        //Create a new warrior
        if (command == "Warrior") {
            addWarrior(commands,warriors);
        }

        //Create a new noble
        else if (command == "Noble") {
            addNoble(commands,nobles);
        }
        
        //Initiate a battle
        else if (command == "Battle") {
            battle(commands, nobles);
        }

        //Hire a warrior
        else if (command == "Hire") {
            hire(commands,nobles,warriors);
        }

        //Fire a warrior
        else if (command == "Fire") {
            fire(commands,nobles,warriors);
        }

        //Print the status for all the warriors
        else if (command == "Status") {
            status(nobles,warriors);
        }

        //Clear all the nobles and warriors
        else if (command == "Clear") {
            clear(nobles,warriors);
        }
        else {
            cerr << "Command not recognized: " << command << endl;
        }
    }
    commands.close(); 
}


    
