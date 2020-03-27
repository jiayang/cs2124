#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pet {
public:
    virtual void eat() {cout<<"eating"<<endl;}
};

class Cat : public Pet {
public:
    void eat() {cout << "Cat eating" << endl;}
};

void foo(Pet pet) {
    pet.eat();
}

int main() {}
