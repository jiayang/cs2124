#include "Registrar.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
//
// Code for Registrar
//
Registrar::Registrar() {};

ostream& operator<<(ostream& os, const Registrar& reg) {
  os << "Registrar's Report\n"
     << "Courses:\n";
  for (const Course* course : reg.courses) {
    os << *course << endl;
  }
  os << "Students:\n";
  for (const Student* student : reg.students) {
    os << *student << endl;
  }
  return os;
}

bool Registrar::addCourse(const string& name) {
  for (const Course* course : courses) {
    if (course->getName() == name) {
      return false;
    }
  }

  Course* newCourse = new Course(name);
  courses.push_back(newCourse);
  return true;
}

bool Registrar::addStudent(const string& name) {
  for (const Student* student : students) {
    if (student->getName() == name) {
      return false;
    }
  }
  Student* newStudent = new Student(name);
  students.push_back(newStudent);
  return true;
}

size_t Registrar::findStudent(const string& name) const {
  for (size_t i = 0; i < students.size(); ++i) {
    if (students[i]->getName() == name) {
      return i;
    }
  }
  return students.size();
}

size_t Registrar::findCourse(const string& name) const {
  for (size_t i = 0; i < courses.size(); ++i) {
    if (courses[i]->getName() == name) {
      return i;
    }
  }
  return courses.size();
}

bool Registrar::enrollStudentInCourse(const string& studentName,
                                      const string& courseName) {
  size_t student_i = findStudent(studentName);
  size_t course_i = findCourse(courseName);

  if (student_i == students.size() || course_i == courses.size()) {
    cerr << "Student or course name does not exist" << endl;
    return false;
  }

  Student* student = students[student_i];
  Course* course = courses[course_i];

  student->addCourse(course);
  course->addStudent(student);

  return true;
}

bool Registrar::cancelCourse(const string& courseName) {
  size_t course_i = findCourse(courseName);
  if (course_i == courses.size()) {
    cerr << "Could not find course: " << courseName;
    return false;
  }

  Course* course = courses[course_i];
  course->removeStudentsFromCourse();

  delete course;
  //Shift everything down by 1
  for (size_t i = course_i; i < courses.size()-1; ++i) {
    courses[i] = courses[i+1];
  }
  courses.pop_back();
}

void Registrar::purge() {
  for (Course* course : courses) {
    delete course;
  }
  for (Student* student : students) {
    delete student;
  }
  courses.clear();
  students.clear();
}

}
