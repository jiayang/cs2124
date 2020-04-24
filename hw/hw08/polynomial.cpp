//Jiayang Chen
//HW08 - polynomial.cpp
//Implement polynomial functions

#include "polynomial.h"
#include <vector>
#include <iostream>
using namespace std;

Node::Node(int val = 0, Node* next = nullptr)
    : next(next), value(val) {}


//Delete the rest of the polynomial starting from a node
void Polynomial::deleteFromNodeOn(Node*& toDelete) {
    while (toDelete != nullptr) {
        Node* holder = toDelete->next;
        delete toDelete;
        toDelete = holder;
    }
}

//purge leading zeros from polynomial
void Polynomial::purgeZeros() {
    Node* lastZero = nullptr;
    Node* cur = head;
    while (cur != nullptr) {
        //Set the marker for latest zero
        if (cur->value == 0 && lastZero == nullptr) {
            lastZero = cur;
        } else if (cur->value != 0) {
            lastZero = nullptr;
        }
        cur = cur->next;
    }

    //Make the last node point to nullptr
    cur = head;
    while (cur->next != lastZero) {
        cur = cur->next;
    }
    cur->next = nullptr;
    
    if (lastZero != nullptr) {
        deleteFromNodeOn(lastZero);
    }
    //If we got rid of everything
    if (head == nullptr) {
        head = new Node();
    }

    
}


//Init to 0
Polynomial::Polynomial() {
    Node* zero = new Node(0);
    head = zero;
}

//Create polynomial from vectors
Polynomial::Polynomial(const vector<int>& coeffs) : head(nullptr) {
    for (int coeff : coeffs) {
        Node* term = new Node(coeff,head);
        head = term;
    }
    purgeZeros();
}

//Copy
Polynomial::Polynomial(const Polynomial& other) {
    const Node* cursor = other.head;

    //Copies the next pointer, but it will end as nullptr or be replaced below
    Node* current = new Node(*other.head); 
    head = current;
    
    while (cursor->next != nullptr) {
        current->next = new Node(*cursor->next);
        cursor = cursor->next;
        current = current->next;
    }
    
    purgeZeros();
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
            if (myCur->next == nullptr && otherCur->next != nullptr) {
                myCur->next = new Node();
            }
            //This is used so we can delete the extra nodes later
            if (otherCur->next != nullptr) {
                myCur = myCur->next;
            }
            otherCur = otherCur->next;
        }

        //If the other is finished but there are extra nodes in current
        Node* next = myCur->next;
        myCur->next = nullptr;
        deleteFromNodeOn(next);
    }
    
    purgeZeros();
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


int Polynomial::evaluate(int x) const {
    int power = 0;
    int total = 0;
    const Node* cursor = head;
    while (cursor != nullptr) {
        total += pow(x, power) * cursor->value;
        power += 1;
        cursor = cursor->next;
    }
    return total;
}

void printHelper(ostream& os, const Node* node, int power) {
    //    cout << node->value;
    if (node->next == nullptr) {
        //If power is greater than 1, show coeff and pow
        if (power > 1) {
            os << node->value << "x^" << power;
        } else if (power == 1) { //if power is 1, only show coeff and x
            if (node->value != 1) {
                os << node->value;
            }
            os << "x";
        } else { //if power is 0, show value
            os << node->value;
        }
    } else {
        //Recursive call
        printHelper(os,node->next,power+1);
        if (node->value != 0) {
            os << " + ";
            //If coefficient is not 1, show value
            if (node->value != 1 || power == 0) {
                os << node->value;
            } 
            if (power > 1) {
                os << "x^" << power;
            } else if (power == 1) {
                os << "x";
            }
        }
    }
}


ostream& operator<<(ostream& os, const Polynomial& poly) {
    printHelper(os, poly.head, 0);
    return os;
}

//a+=other
Polynomial& Polynomial::operator+=(const Polynomial& other)  {
    Node* cur = head;
    Node* otherCur = other.head;
    while (otherCur != nullptr) {
        //Add the values
        //  cout << cur->value << " " << otherCur->value << endl;
        cur->value += otherCur->value;
        //If we need more room
        if (cur->next == nullptr && otherCur->next != nullptr) {
            cur->next = new Node();
        }
        cur = cur->next;
        otherCur = otherCur->next;
    }
    
    purgeZeros();
    return *this;
}
//a+other
Polynomial Polynomial::operator+(const Polynomial& other) {
    Polynomial result = *this;
    result += other;
    result.purgeZeros();
    return result;
}

//a == other
bool Polynomial::operator==(const Polynomial& other) {
    Node* cur = head;
    Node* otherCur = other.head;
    while (otherCur != nullptr || cur != nullptr) {
        //cout << otherCur->value << " " << cur->value << endl;
        if (otherCur->value != cur->value) {
            return false;
        }
        otherCur = otherCur->next;
        cur = cur->next;
    }
    return true;
}

//a != other
bool Polynomial::operator!=(const Polynomial& other) {
    return !(*this == other);
}
