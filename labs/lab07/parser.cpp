#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace BrooklynPoly;


int main() {
  ifstream trans("transactions.txt");
  if (!trans) {
    cerr << "Could not open transactions.txt";
    exit(1);
  }

  Registrar reg;
  
  string command;
  while(trans >> command) {
    if (command == "PrintReport") {
      cout << reg << endl;
    } else if (command == "AddCourse") {
      string coursename;
      trans >> coursename;
      reg.addCourse(coursename);
    } else if (command == "AddStudent") {
      string studentname;
      trans >> studentname;
      reg.addStudent(studentname);
    } else if (command == "EnrollStudentInCourse") {
      string student,course;
      trans >> student >> course;
      reg.enrollStudentInCourse(student,course);
    } else if (command == "CancelCourse") {
      string coursename;
      trans >> coursename;
      reg.cancelCourse(coursename);
    } else if (command == "Purge") {
      reg.purge();
    } else {
      cerr << "Command not recognized: " << command;
      exit(1);
    }
    

  }

}
