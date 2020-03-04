#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream a("basicIO.dcpp");

    if (!a) {
        cerr << "didnt work" << endl;
        exit(1);
    }
    string s;
    a >> s;
    cout << s << endl;;
    
}
