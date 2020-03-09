/*
  Recitation 06
  CS2124 Jiayang Chen
  rec06-origV2.cpp
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

//Initial capacity for directory
const int INITIALCAP = 8;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& dir) {
        cout << "A directory with " << dir.size << " entries:" << endl;
        for (size_t i = 0; i < dir.size; ++i) {
            cout << *dir.entries[i] << endl;
        }
        return os;
    }
public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    Directory() : capacity(INITIALCAP), size(0),
                  entries(new Entry*[INITIALCAP]) {}

    Directory(const Directory& other)
        : capacity(other.capacity), size(other.size),
          entries(new Entry*[other.capacity]) {
        cout << "Trying to copy a directory" << endl;
        for (size_t i = 0; i < other.size; ++i) {
            entries[i] = new Entry(*other.entries[i]);
        }
        cout << "Done copying a directory" << endl;
    }

    ~Directory() {
        //Delete all the individual entries first
        cout << "Trying to delete a directory" << endl;
        for (size_t i = 0; i < size; ++i) {
            delete entries[i];
        }
        //Delete the array
        delete [] entries;
        cout << "Done deleting a directory" << endl;
    }

    //Overload assignment operator
    Directory& operator=(const Directory& other) {
        if (&other != this) {
            for (size_t i = 0; i < size; ++i) {
                delete entries[i];
            }
            delete [] entries;

            entries = new Entry*[other.capacity];
            capacity = other.capacity;
            size = other.size;
            for (size_t i = 0; i < other.size; ++i) {
                entries[i] = new Entry(*other.entries[i]);
            }
        }
        return *this;
    }
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            // something is missing!!!  Add it!
            Entry** data = entries;
            entries = new Entry*[capacity*2];
            for (size_t i = 0; i < size; ++i) {
                entries[i] = data[i];
            }
            delete [] data;
            capacity *= 2;
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    unsigned operator[](const string& name) const {
        for (size_t i = 0; i < size; ++i) {
            //Keep looping and looking forthe name
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }

        //If we could not find that name
        cerr << "Could not find an entry with the name: " << name << endl;
        return 0; 
    } 

private:	
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used?? copy
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
	
} // main
