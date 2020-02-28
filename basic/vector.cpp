/*
  Vector Class
*/

#include <iostream>
using namespace std;

class Vector {
public:
    Vector() : _capacity(8), _size(0) {
        array = new int[_capacity];
    }

    /*
      Vector(size_t size, int value = 0) {
      this = new Vector();
        
    }*/

    ~Vector() { delete [] array; }

    size_t size() const { return theSize; }
    void clear() { _size = 0; }
    
private:
    int* array;
    size_t _capacity;
    size_t _size;
};


int main() {}
