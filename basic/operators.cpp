#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Complex {
    int real;
    int imag;

    explicit operator bool() const {return real == 0 && imag == 0;}

    //PREINCREMENT
    Complex& operator++() {
        ++real;
        return *this;
    }

    //POSTINCREMENT
    Complex operator++(int dummy) {
        Complex original(*this);
        ++real;
        return original;
    }
    

};


Complex operator+(const Complex& a, const Complex& b) {
    Complex c{a.real+b.real,a.imag+b.imag};
    return c;
}

    
int main(){}
