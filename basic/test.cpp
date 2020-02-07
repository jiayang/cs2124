#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream a("foo");
    if (!a) {
	cerr << "Failed\n";
	exit(1);
    }
    int n;
    a >> n;
    cout << n << endl;
}
