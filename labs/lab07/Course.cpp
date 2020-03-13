#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
//Code for Course
Course::Course(const string& name) :name(name) {}

ostream& operator<<(ostream& os, const Course& course) {
  os << course.name << ": ";
  if (course.students.size() == 0) {
    os << "No students";
  } else {
    for (const Student* student : course.students) {
      os << student->getName() << ", ";
    }
  }
  return os;
}

const string& Course::getName() const {
  return name;
}

bool Course::addStudent(Student* student) {
  for (size_t i = 0; i < students.size(); ++i) {
    if (students[i] == student) {
      return false;
    }
  }
  students.push_back(student);
  return true;
}

void Course::removeStudentsFromCourse() {
  for (Student* student : students) {
    student->removedFromCourse(this);
  }
  students.clear();
}
}
