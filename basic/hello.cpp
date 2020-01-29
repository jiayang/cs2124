#include <iostream> //In out
using namespace std; //Set the namespace for the library


void foo() {
  int a = 17;
  cout << "a: " << a << endl;
}

void bar() {
  int b;
  cout << "b: " << b << endl;
}


//Every file needs a main
int main() {
  cout << "Hello World" << endl;
  int x = 10;
  cout << "x: " << x << endl;
  foo();
  bar();
  int y;
  cout << "Enter an int: ";
  cin >> y;
  cout << "y: " << y << endl;
}

