//Jiayang Chen
//HW08 - polynomial.h
//Declaring polynomial functions

#ifndef POLYN

#define POLYN

#include <vector>
#include <iostream>

struct Node {
    Node(int val, Node* next);
    int value;
    Node* next;
};

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
public:
    Polynomial();
    Polynomial(const std::vector<int>& coeffs);
    Polynomial(const Polynomial& other);

    ~Polynomial();
    Polynomial& operator=(const Polynomial& other);

    int evaluate(int x) const;

    Polynomial& operator+=(const Polynomial& other);
    Polynomial operator+(const Polynomial& other);

    bool operator==(const Polynomial& other);
    bool operator!=(const Polynomial& other);
private:
    Node* head;

    void deleteFromNodeOn(Node*& toDelete);
    void purgeZeros();
};

#endif
