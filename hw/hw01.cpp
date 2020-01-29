#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


int main() {
    //Get file stream
    ifstream text("encrypted.txt");

    //Read first number (the number of steps)
    int steps;
    text >> steps;
    //cout << steps << endl;

    //Create vector of lines
    string line;
    vector<string> lines;
    getLine(text,line); //Increment pointer to next line
    while (getLine(text, line)) {
	lines.push_back(line);
    }

    //Loop through all chars in all lines
    for (line : lines) {
	for (int i = 0; i < line.size(); ++i) {
	    char letter = line[i];
	    if (isLowercase(letter)) {
		line[i] = decrypt(letter,steps);
	    }
	}
    }

  
  
  




}

bool isLowercase(char c) {
    //Only lowercase letters are between 'a' and 'z'
    return c >= 'a' && c <= 'z';
}

char decrypt(char c, int stepsToDo) {
    int step = -1;
    if (stepsToDo < 0) {
	step = 1;
    }
    while (stepsToDo != 0) {
	c += step;
	stepsToDo += step;
	if (c <= 'a') {
	    c = 'z';
	} else if (c >= 'z') {
	    c = 'a';
	}
    }
    return c;

}
