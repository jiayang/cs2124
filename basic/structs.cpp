#include <vector>
#include <iostream>
using namespace std;

struct Foo {
    int bar1;
    string bar2;
}; //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<SEMICOLON!!!

int main() {
    vector<Foo> a;
    a.push_back(Foo{1,"hah"});
    a.push_back(Foo());

    
}
