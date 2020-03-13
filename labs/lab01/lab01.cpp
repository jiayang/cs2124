#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//number 13
void displayVectorOfInts(const vector<int>& ints) {
    for (int n : ints) {
        cout << n << " ";
    }
    cout << endl;
}

//number 14
void doubleVectorOfInts(vector<int>& ints) {
    for (size_t i = 0; i < ints.size(); ++i) {
	ints[i] *= 2;
    }
}


//number 15
void doubleWithRangedFor(vector<int>& ints) {
    for (int& n : ints) {
	n *= 2;
    }
}

int main() {
    std::cout << "Hello!" << endl; // number 1
    cout << "Hello!" << endl; // number 2

    // number 3
    int x; 
    cout << "x: " << x << endl;

    //number 4
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "size of x: " << sizeof(x) << endl;
    cout << "size of y: " << sizeof(y) << endl;
    cout << "size of z: " << sizeof(z) << endl;
    cout << "size of pie: " << sizeof(pie) << endl;

    //number 5
    //compile time error
    //x = "felix"; 

    //number 6
    if (y >= 10 && y <= 20) { 
	cout << "y is between 10 and 20" << endl; 
    } else {
	cout << "y is not between 10 and 20" << endl;
    }

    //number 7
    cout << "From the \"for\" loop: " << endl;
    for (int i = 10; i <= 20; ++i) {
	cout << i << endl;
    }
    cout << "From the \"while\" loop: " << endl;
    int i = 10;
    while (i <= 20) {
	cout << i << endl;
	++i;
    }
    cout << "From the \"do while\" loop: " << endl;
    i = 10;
    do {
	cout << i << endl;
	++i;
    } while (i <= 20);

    //number 8
    ifstream ifs;
    string filename;
    do {
	cout << "What is the name of the file?: " << endl;
	cin >> filename;
	ifs.open(filename);
    } while (!ifs);
    
    cout << "Successfully opened " << filename << endl;

    //number 9
    string word;
    while (ifs >> word) {
	cout << word << endl;
    }
    ifs.close();

    //number 10
    vector<int> ints;
    for (int i = 10; i <= 100; i += 2) {
	ints.push_back(i);
    }

    //number 11
    cout << "Numbers in vector (should be all evens from 10 to 100): " << endl;
    for (size_t i = 0; i < ints.size(); ++i) {
	cout << ints[i] << endl;
    }
    for (int n : ints) {
	cout << n << endl;
    }
    for (size_t i = ints.size()-1; i < ints.size(); --i) {
	cout << ints[i] << endl;
    }
    /*
    //number 12
    vector<int> primes{2,3,5,7,11,13,17,19};
    for (int prime : primes) {
	cout << prime << endl;
    }

    //number 13
    displayVectorOfInts(primes);

    //number 14
    doubleVectorOfInts(primes);
    displayVectorOfInts(primes);

    //number 15
    doubleWithRangedFor(primes);
    displayVectorOfInts(primes);*/
}
