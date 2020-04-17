//Jiayang Chen
//HW08 - polynomial.cpp
//Implement polynomial functions

#include "polynomial.h"
#include <vector>
#include <iostream>
using namespace std;

Node::Node(int val = 0, Node* next = nullptr)
    : next(next), value(val) {}


//Init to 0
Polynomial::Polynomial() {
    Node* zero = new Node(0);
    head = zero;
}

//Create polynomial from vectors
Polynomial::Polynomial(const vector<int>& coeffs) : head(nullptr) {
    for (int coeff : coeffs) {
        Node* term = new Node(coeff);
        term->next = head;
        head = term;
    }
}

//Copy
Polynomial::Polynomial(const Polynomial& other) {
    const Node* cursor = other.head;

    //Copies the next pointer, but it will end as nullptr or be replaced below
    Node* current = new Node(*other.head); 

    while (cursor->next != nullptr) {
        current->next = new Node(*cursor->next);
        cursor = cursor->next;
        current = current->next;
    }

    head = current;
}

//Delete the rest of the polynomial starting from a node
void Polynomial::deleteFromNodeOn(Node*& toDelete) {
    while (toDelete != nullptr) {
        Node* holder = toDelete->next;
        delete toDelete;
        toDelete = holder;
    }
}

//Destructor
Polynomial::~Polynomial() {
    deleteFromNodeOn(head);
}



Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (&other != this) {
        const Node* otherCur = other.head;
        Node* myCur = head;
        while (otherCur != nullptr) {
            myCur->value = otherCur->value;
            if (myCur->next == nullptr) {
                //Make a node to go to, node will be deleted if extra
                myCur->next = new Node();
            }
            myCur = myCur->next;
            otherCur = otherCur->next;
        }

        //If the other is finished but there are extra nodes in current
        deleteFromNodeOn(myCur);
    }
    return *this;
}

int pow(int base, int power) {
    int ans = 1;
    while (power > 0) {
        ans *= base;
        --power;
    }
    return ans;
}


int Polynomial::eval(int x) const {
    int power = 0;
    int total = 0;
    const Node* cursor = head;
    while (cursor != nullptr) {
        total += pow(x, power) * cursor->value;
        power += 1;
    }
    return total;
}

ostream& operator<<(ostream& os, const Polynomial& poly) {
    
}
