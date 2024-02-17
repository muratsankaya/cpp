
/*
  rec07_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    //// Course methods needed by Registrar
    Course(const string& name);
    const string& getName() const;
    bool addStudent(Student* studentPtr);
    void removeStudentsFromCourse();
    void removeStudentFromCourse(Student* studentPtr);

private:
    size_t studentSearch(const Student* ptr) const;

    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* coursePtr);
    // Student method needed by Course
    void removedFromCourse(Course*);
    void changeName(const string& name);
    void removeSelf();

private:
    size_t courseSearch(const Course* ptr) const;
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& coursename);
    bool addStudent(const string& studentname);
    bool enrollStudentInCourse(const string& studentName, const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();
    bool changeStudentName(const string& name, const string& newName);
    void dropStudentFromCourse(const string& name, const string& course);
    void removeStudent(const string& name);

private:
    size_t findStudent(const string& studentname) const;
    size_t findCourse(const string& coursename) const;

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


    // [OPTIONAL - do later if time]
    /*cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  */


    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;


    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;

    ifstream ifs("transactions.txt");
    if (!ifs) {
        cerr << "could not open the file " << endl;
        exit(1);
    }

    string command;
    string studentname;
    string coursename;
    while (ifs >> command) {
        if (command == "PrintReport") {
            cout << registrar;
        }
        else if (command == "AddCourse") {
            ifs >> coursename;
            registrar.addCourse(coursename);
        }
        else if (command == "AddStudent") {
            ifs >> studentname;
            registrar.addStudent(studentname);
        }
        else if (command == "EnrollStudentInCourse") {
            ifs >> studentname >> coursename;
            registrar.enrollStudentInCourse(studentname, coursename);
        }
        else if (command == "CancelCourse") {
            ifs >> coursename;
            registrar.cancelCourse(coursename);
        }
    }

}

//Registrar

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report\n";
    os << "Courses:\n";
    for (size_t i = 0; i < rhs.courses.size(); ++i) {
        os << *(rhs.courses[i]) << endl;
    }
    os << "Students:\n";
    for (size_t i = 0; i < rhs.students.size(); ++i) {
        os << *(rhs.students[i]) << endl;
    }
    return os;
}

Registrar::Registrar() {};

bool Registrar::addCourse(const string& coursename) {
    if (findCourse(coursename) == courses.size()) {
        courses.push_back(new Course(coursename));
        return true;
    }
    cerr << coursename << " is already registered\n";
    return false;
}
bool Registrar::addStudent(const string& studentname) {
    if (findStudent(studentname) == students.size()) {
        students.push_back(new Student(studentname));
        return true;
    }
    cerr << studentname << " is already registered\n";
    return false;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    size_t courseIndex = findCourse(courseName);
    size_t studentIndex = findStudent(studentName);
    if (courseIndex == courses.size() || studentIndex == students.size()) { return false; }
    if (!courses[courseIndex]->addStudent(students[studentIndex]) ||
        !students[studentIndex]->addCourse(courses[courseIndex])) {
        cerr << studentName << " is already enrolled in " << courseName << endl;
        return false;
    }
    return true;
}


size_t Registrar::findStudent(const string& studentname) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i]->getName() == studentname) {
            return i;
        }
    }
    return students.size();
}
size_t Registrar::findCourse(const string& coursename) const {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i]->getName() == coursename) {
            return i;
        }
    }
    return courses.size();
}

bool Registrar::cancelCourse(const string& courseName) {
    size_t courseIndex = findCourse(courseName);
    if (courseIndex != courses.size()) {
        courses[courseIndex]->removeStudentsFromCourse();
        delete courses[courseIndex];
        for (size_t i = courseIndex; i < courses.size() - 1; ++i) {
            courses[i] = courses[i + 1];
        }
        courses.pop_back();
        return true;
    }
    cerr << "There is not a course called: " << courseName << endl; return false;
}

void Registrar::purge() {
    for (size_t i = 0; i != courses.size(); ++i) {
        delete courses[i];
    }
    for (size_t i = 0; i != students.size(); ++i) {
        delete students[i];
    }
    students.clear();
    courses.clear();
}

bool Registrar::changeStudentName(const string& name, const string& newName) {
    size_t studentIndex = findStudent(name);
    if (studentIndex != students.size()) {
        students[studentIndex]->changeName(newName);
        return true;
    }
    cerr << "There is one called with the name: " << name;
}

void Registrar::dropStudentFromCourse(const string& name, const string& course) {
    size_t courseIndex = findCourse(course);
    size_t studentIndex = findStudent(name);
    courses[courseIndex]->removeStudentFromCourse(students[studentIndex]);
}

void Registrar::removeStudent(const string& name) {
    size_t studentIndex = findStudent(name);
    students[studentIndex]->removeSelf();
    delete students[studentIndex];
    for (size_t i = studentIndex; i < students.size() - 1; ++i) {
        students[i] = students[i + 1];
    }
    students.pop_back();
}


//Student

ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if (rhs.students.size() == 0) { os << "No Students"; return os; }
    for (size_t i = 0; i < rhs.students.size(); ++i) {
        os << rhs.students[i]->getName() << " ";
    }
    return os;
}

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const { return name; }

bool Student::addCourse(Course* coursePtr) {
    if (courseSearch(coursePtr) == courses.size()) {
        courses.push_back(coursePtr);
        return true;
    }
    return false;
}

size_t Student::courseSearch(const Course* ptr) const {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == ptr) {
            return i;
        }
    }
    return courses.size();
}

void Student::removedFromCourse(Course* ptr) {
    size_t courseIndex = courseSearch(ptr);
    for (size_t i = courseIndex; i < courses.size() - 1; ++i) {
        courses[i] = courses[i + 1];
    }
    courses.pop_back();
}

void Student::changeName(const string& name) {
    this->name = name; //why just name = name won't work?
}


void Student::removeSelf() {
    for (Course* ptr : courses) {
        ptr->removeStudentFromCourse(this);
    }
    courses.clear();
}



//Course

ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.size() == 0) { os << "No Courses"; return os; }
    for (size_t i = 0; i < rhs.courses.size(); ++i) {
        os << rhs.courses[i]->getName() << " ";
    }
    return os;
}

Course::Course(const string& name) : name(name) {}

const string& Course::getName() const { return name; }

bool Course::addStudent(Student* studentPtr) {
    if (studentSearch(studentPtr) == students.size()) {
        students.push_back(studentPtr);
        return true;
    }
    return false;
}

size_t Course::studentSearch(const Student* ptr) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i] == ptr) {
            return i;
        }
    }
    return students.size();
}

void Course::removeStudentsFromCourse() {
    for (Student* ptr : students) {
        ptr->removedFromCourse(this);
    }
    students.clear();
}

void Course::removeStudentFromCourse(Student* studentPtr) {
    size_t studentPtrIndex = studentSearch(studentPtr);
    studentPtr->removedFromCourse(this);
    for (size_t i = studentPtrIndex; i < students.size() - 1; ++i) {
        students[i] = students[i + 1];
    }
    students.pop_back();
}

