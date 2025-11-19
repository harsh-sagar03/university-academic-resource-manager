#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
// -------------------- COURSE CLASS --------------------
class Course {
  public:
    int id;            // CourseId (simple int)
    string name;
    int credits;

    Course(int i,string n, int c) {
        id = i;
        name = n;
        credits = c;
    }

    // Default constructor
    Course() {
        id = 0;
        name = "";
        credits = 0;
    }

};

// -------------------- GLOBAL HASH TABLE --------------------
unordered_map<int, Course> courseTable; //Store and access courses by ID quickly



// -------------------- COURSE FUNCTIONS --------------------

// Insert a new course
void insertCourse(const Course& c) {
    courseTable[c.id] = c;
}

// Find a course by ID
Course* findCourseById(const int& id) {
    auto it = courseTable.find(id);
    if (it != courseTable.end()) {
        return &it->second; // found
    }
    return nullptr; // not found
}

// Remove a course by ID
void removeCourseById(const int& id) {
    courseTable.erase(id);
}

// Check if a course exists
bool containsCourse(const int& id) {
    return courseTable.find(id) != courseTable.end();
}

// -------------------- MAIN FUNCTION (DEMO) --------------------
int main() {
    insertCourse(Course(101, "Data Structures", 4));
    insertCourse(Course(102, "Calculus", 3));

    int searchId = 101;

    if (containsCourse(searchId)) {
        Course* c = findCourseById(searchId);
        cout << "Found: " << c->name << " (" << c->credits << " credits)\n";
    }

    removeCourseById(searchId);

    if (!containsCourse(searchId)) {
        cout << "Course removed successfully.\n";
    }

    return 0;
}



#include <iostream>
#include <string>
#include <unordered_map>

// -------------------- STUDENT CLASS --------------------
class Student {
public:
    int id;              // StudentId (simple integer)
    string name;

    // Constructor
    Student(int i = 0, string n = "") {
        id = i;
        name = n;
    }
};

// -------------------- GLOBAL HASH TABLE --------------------
unordered_map<int, Student> studentTable;

// -------------------- STUDENT FUNCTIONS --------------------

// Insert a new student
void insertStudent(const Student& s) {
    studentTable[s.id] = s;
}

// Find a student by ID
Student* findStudentById(const int& id) {
    auto it = studentTable.find(id);
    if (it != studentTable.end()) {
        return &it->second; // found
    }
    return nullptr; // not found
}

// Remove a student by ID
void removeStudentById(const int& id) {
    studentTable.erase(id);
}

// Check if a student exists
bool containsStudent(const int& id) {
    return studentTable.find(id) != studentTable.end();
}

// -------------------- MAIN FUNCTION (DEMO) --------------------
int main() {
    insertStudent(Student(1, "Alice"));
    insertStudent(Student(2, "Bob"));
    insertStudent(Student(3, "Charlie"));

    int searchId = 2;

    if (containsStudent(searchId)) {
        Student* s = findStudentById(searchId);
        cout << "Found student: " << s->name << "\n";
    }

    removeStudentById(searchId);

    if (!containsStudent(searchId)) {
        cout << "Student removed successfully.\n";
    }

    return 0;
}





#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// -------------------- ASSIGNMENT CLASS --------------------
class Assignment {
public:
    string id;       // string key, e.g., "A101"
    string title;
    string dueDate;
    bool completed;

    // Constructor
    Assignment(string i = "", string t = "", string d = "", bool c = false) {
        id = i;
        title = t;
        dueDate = d;
        completed = c;
    }
};

// -------------------- GLOBAL HASH TABLE --------------------
unordered_map<string, Assignment> assignmentTable;

// -------------------- ASSIGNMENT FUNCTIONS --------------------

// Insert a new assignment
void insertAssignment(const Assignment& a) {
    assignmentTable[a.id] = a;
}

// Find an assignment by ID
Assignment* findAssignmentById(const string& id) {
    auto it = assignmentTable.find(id);
    if (it != assignmentTable.end()) {
        return &it->second;
    }
    return nullptr;
}

// Remove an assignment by ID
void removeAssignmentById(const string& id) {
    assignmentTable.erase(id);
}

// Check if an assignment exists
bool containsAssignment(const string& id) {
    return assignmentTable.find(id) != assignmentTable.end();
}

// -------------------- MAIN FUNCTION (DEMO) --------------------
int main() {
    // Insert assignments
    insertAssignment(Assignment("A101", "Math Homework", "2025-10-30"));
    insertAssignment(Assignment("A102", "Science Project", "2025-11-05"));

    string searchId = "A101";

    // Find and display assignment
    if (containsAssignment(searchId)) {
        Assignment* a = findAssignmentById(searchId);
        cout << "Found assignment: " << a->title
        cout << ", due: " << a->dueDate
        cout << ", completed: " << (a->completed ? "Yes" : "No") << "\n";
    }

    // Remove assignment
    removeAssignmentById(searchId);

    // Check if removed
    if (!containsAssignment(searchId)) {
        cout << "Assignment " << searchId << " removed successfully.\n";
    }

    return 0;
}
