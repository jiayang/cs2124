#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

/*
  functions for use with CS2124 rec11
  -jbs
*/

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

void splice(Node* other, Node* location) {
    Node* next = location->next;
    location->next = other;
    while (other->next != nullptr) {
        other = other->next;
    }
    other->next = next;
}

ostream& operator<<(ostream& os, const Node* list) {
    while (list != nullptr) {
        os << list->data << " ";
        list = list->next;
    }
    return os;
}

Node* isSublist(Node* find, Node* list) {
    Node* reset = find; //As a save for the pattern
    Node* currentFind = find; //The current data we are looking for
    Node* startPos = nullptr; //The start position of the answer

    while (list != nullptr) {
        //        cout << list->data << " " << currentFind->data << endl;
        if (list->data == currentFind->data) {
            if (startPos == nullptr) {
                startPos = list;
            }
            currentFind = currentFind->next;
            list = list->next;
            if (currentFind == nullptr) { //we are done
                return startPos;
            }
        } else {
            if (startPos != nullptr) {
                list = startPos;
            }
            currentFind = reset;
            startPos = nullptr;
            list = list->next;
        }
    }

    return nullptr;
}

Node* sharedListBruteForce(Node* a, Node* b) {
    while (a != nullptr) {
        Node* curr = b;
        while (curr != nullptr) {
            if (a == curr) {
                return curr;
            }
            curr = curr->next;
        }
        a = a->next;
    }
    return nullptr;
}

Node* sharedListUsingSet(Node* a, Node* b) {
    unordered_set<Node*> find;
    while (a != nullptr) {
        find.insert(a);
        a = a->next;
    }
    while (b != nullptr) {
        if (find.find(b) != find.end()) {
            return b;
        }
        b = b->next;
    }
    return nullptr;
}

int main() {
    Node* a = listBuild({1,2,3,6,7,8,9,10});
    Node* b = listBuild({4,5});
    Node* c = listBuild({3,1,2});
    
    a->next = c;
    b->next = c;

    cout << sharedListBruteForce(a,b) << endl;
    cout << sharedListUsingSet(a,b) << endl;
    cout << sharedListUsingSet(a,c) << endl;
    /*cout << "Part One:\n"
         << "a: " << a << endl
         << "b: " << b << endl;

    Node* spliceLoc = a->next->next;
    cout << "Splicing b into a" << endl;
    splice(b, spliceLoc);
    cout << "New a: " << a << endl;

    cout << "Testing isSublist" << endl;
    Node* c = listBuild({4,5,6});
    cout << "c: " << c << endl;
    cout << "c is sublist of a?: " << isSublist(c,a) << endl;

    Node* d = listBuild({5,6,7});
    cout << "d: " << d << endl;
    cout << "d is sublist of a? (empty means no): " << isSublist(d,a) << endl;

    Node* e = listBuild({1,2,3,2,3,2,4,5,6});
    cout << "e: " << e << endl;
    cout << "d is sublist of e?: " << isSublist(d,e) << endl;
    */
}
