//Jiayang Chen
//hw03.cpp
//Creating warriors that fight each other to the death
//This time, using classes!

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


//Warriors, who have names and a weapon
class Warrior {
    //Overloading output operator for warrior
    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << "Warrior: " << warrior.name
           << ", " << warrior.weapon;
        return os;
    }
public:
    Warrior(const string& myName, const string& weaponName, int strength)
        : name(myName), weapon(weaponName, strength) {};

    //Gets the strength of the warrior's weapon
    int strength() const {
        return weapon.strength();
    }

    //Sets the strength of the warrior's weapon
    void setStrength(int newStrength) {
        weapon.setStrength(newStrength);
    }

    //Battle between two warriors, prints result of battle
    //Modifies the strength of both warriors
    void battle(Warrior& other) {
        cout << name << " is battling " << other.name << endl;
    
        //If warrior 1 is dead
        if (strength() == 0) {
            //If warrior 2 is ALSO dead
            if (other.strength() == 0) {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            } else {
                cout << "He's dead," << other.name << endl;
            }
        }
        
        //If warrior 2 is dead
        else if (other.strength() == 0) {
            cout << "He's dead, " << name << endl;
        }
        
        //If warrior 1 is stronger
        else if (strength() > other.strength()) {
            setStrength(strength() - other.strength());
            other.setStrength(0);
            cout << name << " defeats " << other.name << endl;
        }
        
        //If warrior 2 is stronger
        else if (strength() < other.strength()) {
            other.setStrength(other.strength() - strength());
            setStrength(0);
            cout << other.name << " defeats " << name << endl;
        }
        
        //If both warriors are equally strong
        else {
            setStrength(0);
            other.setStrength(0);
            cout << "Mutual Annihilation: "
                 << name << " and " << other.name
                 << " die at each other's hands!" << endl;
        }    
    }

    //Gets the name of the warrior
    const string& getName() const {
        return name;
    }
private:
    //Each warrior has their own weapon
    class Weapon {
        friend ostream& operator<<(ostream& os, const Weapon& weapon) {
            os << "Weapon: " << weapon.name << ", " << weapon.str;
            return os;
        }
    public:
        Weapon(const string& weaponName, int strength)
            : name(weaponName), str(strength) {};

        //Gets strength of weapon
        int strength() const {
            return str;
        }

        //Changes the strength weapon to desired val
        void setStrength(int newStrength) {
            str = newStrength;
        }
        
    private:
        string name;
        int str;
    };

    string name;
    Weapon weapon;
};


size_t findWarrior(const vector<Warrior>& warriors, const string& name);
void addWarrior(ifstream& commands, vector<Warrior>& warriors);
void status(const vector<Warrior>& warriors);



//Finds a warrior from a vector given a name
size_t findWarrior(const vector<Warrior>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].getName() == name) {
            return i;
        }
    }
    cout << "Could not find the warrior" << endl;
}

//Creates a warrior from the stream and adds it to the vector of warriors
void addWarrior(ifstream& commands, vector<Warrior>& warriors) {
    string name;
    string weaponName;
    int str;
    commands >> name >> weaponName >> str;
    warriors.emplace_back(name,weaponName,str);
}

//Prints the status of all the warriors
void status(const vector<Warrior>& warriors) {
    cout << "There are " << warriors.size() << " warriors." << endl;
    for (const Warrior& warrior : warriors) {
        cout << warrior << endl;
    }
}



    

//Reads "warriors.txt" for the specific commands given
int main() {
    ifstream commands("warriors.txt");
    if (!commands) {
        cerr << "Could not open warriors.txt" << endl;
        exit(1);
    }

    vector<Warrior> warriors; //Vector of warriors
    
    string command;
    //While there are still commands to execute
    while (commands >> command) {
        //Create a new warrior
        if (command == "Warrior") {
            addWarrior(commands,warriors);
        }

        //Initiate a battle
        else if (command == "Battle") {
            string name1, name2;
            commands >> name1 >> name2;
            Warrior& warrior1 = warriors[findWarrior(warriors, name1)];
            Warrior& warrior2 = warriors[findWarrior(warriors, name2)];
            warrior1.battle(warrior2);
        }

        //Print the status for all the warriors
        else if (command == "Status") {
            status(warriors);
        }

        else {
            cerr << "Command not recognized: " << command << endl;
        }
    }
    commands.close(); 
}

