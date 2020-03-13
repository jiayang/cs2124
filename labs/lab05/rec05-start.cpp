/*
  rec05.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//A timeslot for a section
class Timeslot {
public:
    Timeslot(const string& theDay, int timeOfDay)
        : day(theDay), time(timeOfDay) {}
    
    friend ostream& operator<<(ostream& os, const Timeslot& time) {
        string trail("am");
        if (time.time > 12) {
            trail = "pm";
        }
        os << "Time slot: [Day: " << time.day << ", Start time: "
           << (time.time % 12) << trail << "]";
        return os;
    } 
private:
    string day;
    int time;
};

class StudentRecord {
public:
    StudentRecord(const string& aName) : name(aName), grades(14,-1) {}

    friend ostream& operator<<(ostream& os, const StudentRecord& record) {
        os << "Name: " << record.name << ", Grades: ";
        for (int grade : record.grades) {
            os << grade << " ";
        }
        return os;
    }

    string getName() const { return name; }

    //Change the grade for a given week
    void changeGrade(int grade, int week) {
        grades[week - 1] = grade; // -1 because grades start at week 1
    }

    //Get all the grades
    vector<int> getGrades() const { return grades; }
private:
    string name;
    vector<int> grades;
};
    
class Section {
public:
    Section(const string& theName, const string& day, int timeOfDay)
        : name(theName), time(day, timeOfDay) {};

    friend ostream& operator<<(ostream& os, const Section& sec) {
        os << "Section: " << sec.name
           << ", " << sec.time << ", Students: ";
        
        if (sec.records.size() == 0) {
            os << "None";
        } else {
            os << endl;
            for (StudentRecord* record : sec.records) {
                os << *record << endl;
            }
        }
        return os;
    }

    //Adds a student record pointer to the vector
    void addStudent(const string& name) {
        StudentRecord* newStudent = new StudentRecord(name);
        records.push_back(newStudent);
    }

    //Adds the grade for a student in a given week
    void addGrade(const string& studentName, int grade, int week) {
        for (StudentRecord* record : records) {
            if (record->getName() == studentName) {
                record->changeGrade(grade,week);
            }
        }
    }

    //Clear only the students
    void reset() {
        cout << "Removing students in section " << name << endl;
        for (StudentRecord* record : records) {
            cout << "Deleting " << record->getName() << endl;
            delete record;
            
        }
    }
    ~Section() {
        cout << "Section " << name << " is being deleted" << endl;
        for (StudentRecord*& record : records) {
            cout << "Deleting " << record->getName() << endl;
            delete record;
            record = nullptr;
        }
    }
    
    Section(const Section& sec) : name(sec.name), records(), time(sec.time) {
        for (StudentRecord* record : sec.records) {
            //Create the copy
            StudentRecord* aCopy = new StudentRecord(*record);
            records.push_back(aCopy);
        } 
    }
private:
    string name;
    vector<StudentRecord*> records;
    Timeslot time;
};

class LabWorker {
public:
    LabWorker(const string& aName) : name(aName), section(nullptr) {};

    friend ostream& operator<<(ostream& os, const LabWorker& worker) {
        if (worker.section) {
            os << worker.name << " has " << *worker.section;
        } else {
            os << worker.name << " does not have a section";
        }
        return os;
    }

    void addSection(Section& sec) {
        section = &sec;
    }

    void addGrade(const string& name, int grade, int week) {
        section->addGrade(name,grade,week);
    }
private:
    string name;
    Section* section;
};



// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
