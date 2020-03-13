/*
  rec07 
  Starter Code for required functionality
  Yes, you may add other methods.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

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
