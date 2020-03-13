#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
//Code for Student
Student::Student(const string& name) :name(name) {}

ostream& operator<<(ostream& os, const Student& student) {
  os << student.name << ": ";
  if (student.courses.size() == 0) {
    os << "No courses";
  } else {
    for (const Course* course : student.courses) {
      os << course->getName() << ", ";
    }
  }
  return os;
}

const string& Student::getName() const {
  return name;
}

bool Student::addCourse(Course* course) {
  for (size_t i = 0; i < courses.size(); ++i) {
    if (courses[i] == course) {
      return false;
    }
  }
  courses.push_back(course);
  return true;
}

void Student::removedFromCourse(Course* course) {
  bool found = false;
  for (size_t i = 0; i < courses.size(); ++i) {
    if (courses[i] == course) {
      found = true;
    } else if (found) {
      courses[i-1] = courses[i];
    }
  }
  courses.pop_back();
}
}
