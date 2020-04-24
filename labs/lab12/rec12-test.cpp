// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& list) {
        Node* cur = list.header->next;
        while (cur != list.trailer) {
            cout << cur->value << " ";
            cur = cur->next;
        }
        return os;
    }
private:
    struct Node {
        Node(int data = 0, Node* prev = nullptr, Node* next = nullptr)
            : value(data), prev(prev), next(next) {}
        Node* prev;
        Node* next;
        int value;
    };
    
    size_t _size;
    Node* header;
    Node* trailer;

public:    
    class iterator {
        friend List;
    public:
        iterator(Node* node) : node(node) {}
        
        iterator& operator++() {
            node = node->next;
            return *this;
        }

        iterator& operator--() {
            node = node->prev;
            return *this;
        }

        bool operator==(const iterator& other) const {
            return other.node == node;
        }

        bool operator!=(const iterator& other) const {
            return !(other == *this);
        }

        const int& operator*() const {
            return node->value;
        }
        int& operator*() {
            return node->value;
        }
    private:
        Node* node;  
    };
    
    List() : _size(0), header(new Node()), trailer(new Node()) {
        header->next = trailer;
        trailer->prev = header;
    }

    void push_front(int data) {
        Node* next = header->next;
        Node* newNode = new Node(data,header,next);
        header->next = newNode;
        next->prev = newNode;
        ++_size;
    }

    void pop_front() {
        if (_size == 0) {
            cout << "Trying to delete from empty list!" << endl;
            return;
        }
        Node* newFirst = header->next->next;
        Node* oldFirst = header->next;
        int val = oldFirst->value;
        delete oldFirst;
        newFirst->prev = header;
        header->next = newFirst;
        --_size;
    }
    
    void push_back(int data) {
        Node* previous = trailer->prev;
        Node* newNode = new Node(data,previous,trailer);
        previous->next = newNode;
        trailer->prev = newNode;
        ++_size;
    }

    void pop_back() {
        if (_size == 0) {
            cout << "Trying to delete from empty list!" << endl;
            return;
        }
        Node* newLast = trailer->prev->prev;
        Node* oldLast = trailer->prev;
        int val = oldLast->value;
        delete oldLast;
        newLast->next = trailer;
        trailer->prev = newLast;
        --_size;
    }

    int& front() {
        if (_size == 0) {
            cout << "trying to access from empty list!" << endl;
            exit(1);
        }
        return header->next->value;
    }

    int front() const {
        if (_size == 0) {
            cout << "trying to access from empty list!" << endl;
            exit(1);
        }
        return header->next->value;
    }

    int& back() {
        if (_size == 0) {
            cout << "trying to access from empty list!" << endl;
            exit(1);
        }
        return trailer->prev->value;
    }

    int back() const {
        if (_size == 0) {
            cout << "trying to access from empty list!" << endl;
            exit(1);
        }
        return trailer->prev->value;
    }

    size_t size() const {
        return _size;
    }

    void clear() {
        Node* cur = header->next;
        while (cur != trailer) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        header->next = trailer;
        trailer->prev = header;
        _size = 0;
    }

    int& operator[](int index) {
        Node* cur = header->next;
        while (index > 0) {
            cur = cur->next;
            --index;
        }
        return cur->value;
    }
    
    int operator[](int index) const {
        Node* cur = header->next;
        while (index > 0) {
            cur = cur->next;
            --index;
        }
        return cur->value;
    }

    iterator begin() {return iterator(header->next);}
    iterator end() {return iterator(trailer);}


    iterator& insert(iterator iter, int val) {
        Node* prev = iter.node->prev;
        prev->next = new Node(val,prev,iter.node);
        iter.node->prev = prev->next;
        ++_size;
    }

    iterator& erase(iterator iter) {
        Node* prev = iter.node->prev;
        Node* next = iter.node->next;
        prev->next = next;
        next->prev = prev;
        delete iter.node;
        iter.node = next;
        --_size;
    }
};

// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList
         << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

//Task 4
void printListSlow(const List& myList) {
 for (size_t i = 0; i < myList.size(); ++i) {
     cout << myList[i] << ' ';
 }
 cout << endl;
}
/*
// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    
*/
int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    
    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    
    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
  
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";
    
 // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
    /*
    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    */
}
