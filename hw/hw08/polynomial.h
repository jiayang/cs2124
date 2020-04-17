//Jiayang Chen
//HW08 - polynomial.h
//Declaring polynomial functions

#ifndef POLYN

#define POLYN

#include <vector>

struct Node {
    Node(int val, Node* next);
    int value;
    Node* next;
};

class Polynomial {
public:
    Polynomial();
    Polynomial(const std::vector<int>& coeffs);
    Polynomial(const Polynomial& other);

    ~Polynomial();
    Polynomial& operator=(const Polynomial& other);

    int eval(int x) const;
private:
    Node* head;

    void deleteFromNodeOn(Node*& toDelete);
};

#endif
