#include <vector>
#include <iostream>
#include <fstream>
using namespace std;



bool isLowercase(char c) {
    //Only lowercase letters are between 'a' and 'z'
    return c >= 'a' && c <= 'z';
}

char decrypt(char c, int steps) {
    //Take the number of steps
    c -= steps;

    //Check for out of bounds
    if (c > 'z') {
        int difference = c - 'z';
        c = 'a' + (difference-1); //-1 because we want to start at 'a'
    } else if (c < 'a') {
        int difference = 'a' - c;
        c = 'z' - (difference-1); //same as above
    }
    return c;

}

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
    getline(text,line); //Increment pointer to next line
    while (getline(text, line)) {
	//cout << line << endl;
	lines.push_back(line);
    }
    text.close();
    
    //Loop through all chars in all lines and decrypt
    for (int linenum = 0; linenum < lines.size(); ++linenum) {
	line = lines[linenum];
	for (int i = 0; i < line.size(); ++i) {
	    char letter = line[i];
	    if (isLowercase(letter)) {
		lines[linenum][i] = decrypt(letter,steps);
	    }
	}
    }

    //Print ans
    for (int i = lines.size() - 1; i >= 0; --i) {
        cout << lines[i] << endl;
    }

    return 0;

}
