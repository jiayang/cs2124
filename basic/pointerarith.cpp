#include <iostream>
#include <vector>
using namespace std;



int main() {
    int* array = new int[10,9,8,7];
    *(array+1) = 2;
    
    cout << *(array+1) << endl;
    cout << array[1] << endl;

    delete [] array;
}


