#include <iostream>
using namespace std;

struct Person {
  Person() : name() { }
  void display() {
    cout << "Person: " << name << endl;
  }
  string name;
};


int main() {
  Person john;
  john.name = "John";
  john.display();

  cout << 1 << endl;
}
