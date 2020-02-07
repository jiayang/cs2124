//Jiayang Chen
//HW 02 - Creating warriors that fight each other

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


//Warriors, who have names and strength
struct Warrior {
  Warrior(const string& myName, int strength) : name(myName), str(strength) {};
    string name;
    int str;
};


//Battle between two warriors, prints result of battle
void battle(Warrior& warrior1, Warrior& warrior2) {
    cout << warrior1.name << " is battling " << warrior2.name << endl;
    
    //If warrior 1 is dead
    if (warrior1.str == 0) {
	//If warrior 2 is ALSO dead
	if (warrior2.str == 0) {
	    cout << "Oh, NO! They're both dead! Yuck!" << endl;
	} else {
	    cout << "He's dead," << warrior2.name << endl;
	}
    }
    
    //If warrior 2 is dead
    else if (warrior2.str == 0) {
	cout << "He's dead, " << warrior1.name << endl;
    }

    //If warrior 1 is stronger
    else if (warrior1.str > warrior2.str) {
	warrior1.str -= warrior2.str;
	warrior2.str = 0;
	cout << warrior1.name << " defeats " << warrior2.name << endl;
    }

    //If warrior 2 is stronger
    else if (warrior1.str < warrior2.str) {
	warrior2.str -= warrior1.str;
	warrior1.str = 0;
	cout << warrior2.name << " defeats " << warrior1.name << endl;
    }

    //If both warriors are equally strong
    else {
	warrior1.str = 0;
	warrior2.str = 0;
	cout << "Mutual Annihilation: "
	     << warrior1.name << " and " << warrior2.name
	     << " die at each other's hands!" << endl;
    }
}

//Finds a warrior from a vector given a name
Warrior& findWarrior(vector<Warrior>& warriors, const string& name) {
    for (Warrior& aWarrior : warriors) {
	if (aWarrior.name == name) {
	    return aWarrior;
	}
    }
    cout << "Could not find the warrior" << endl;
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
	    string name;
	    int str;
	    commands >> name >> str;
	    warriors.push_back(Warrior(name,str));
	}

	//Initiate a battle
	else if (command == "Battle") {
	    string name1;
	    string name2;
	    commands >> name1 >> name2;
	    Warrior& warrior1 = findWarrior(warriors, name1);
	    Warrior& warrior2 = findWarrior(warriors, name2);
	    battle(warrior1, warrior2);
	}

	//Print the status for all the warriors
	else if (command == "Status") {
	    for (const Warrior& warrior : warriors) {
		cout << "Warrior: " << warrior.name
		     << ", strength: " << warrior.str << endl;
	    }
	}

	else {
	    cerr << "Command not recognized: " << command << endl;
	}


    }

    commands.close();
    
}

