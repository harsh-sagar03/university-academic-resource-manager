#ifndef STUDENT_SCHEDULE_H
#define STUDENT_SCHEDULE_H
#include <string>
#include <vector>
using namespace std;
/*

    STUDENT SCHEDULE MODULE (Part B)
    --------------------------------
    This module manages student schedules using a
    multi-list structure. Each student can enroll in
    multiple courses, and each course can have multiple
    students. This is essentially a many-to-many mapping.

    How to use:
    - Include this header in main.cpp (or any other file).
    - Implement the functions in student_schedule.cpp.
    - Do NOT write full logic here (only declarations).

*/

// -------------------- TYPEDEFS --------------------

// -------------------- STRUCT DEFINITIONS --------------------
/*
   Represents a student with:
   - id   : Unique integer identifier
   - name : Student's full name
*/
class Student {
private:
    int id;
    string name;
    string department;
    // (Optionally: year etc. can be added later)
// Constructors
public:
// Default Constructor
Student();

// Parameterized Constructor
Student(int id,string name,string department){
    this->id=id;
    this->name=name;
    this->department=department;
}

int getId() const { return id; }
string getName() const { return name; }
string getDepartment() const { return department; }

void setId(int newId) { id = newId; }
void setName(const string &newName) { name = newName; }
void setDepartment(const string &newDept) { department = newDept; }

};



// -------------------- FUNCTION DECLARATIONS --------------------
/*
   Adds a new student into the system.
   - Input: const reference to Student object
*/
void addStudent(const Student& s);

/*
   Removes a student completely (and drops all their enrollments).
   - Input: StudentId
*/
void removeStudent(const int& id); //removeStudent: must also clean up all their course enrollments.

/*
   Enrolls a student in a course.
   - Input: StudentId, CourseId
*/
void enrollStudentInCourse(const int& sid, const int& cid);

/*
   Drops a student from a specific course.
   - Input: StudentId, CourseId
*/
void dropStudentFromCourse(const int& sid, const int& cid);

/*
   Displays the full schedule (list of courses) for a student.
   - Input: StudentId
*/
void displayStudentSchedule(const int& sid);

/*
   Checks if a student is enrolled in a given course.
   - Input: StudentId, CourseId
   - Output: true if enrolled, false otherwise
*/
bool isStudentEnrolledInCourse(const int& sid, const int& cid);

/*
   Gets all courses that a student is enrolled in.
   - Input: StudentId
   - Output: vector of CourseId
*/
vector<int> getStudentCourses(const int& sid);

/*
   Gets all students who are enrolled in a given course.
   - Input: CourseId
   - Output: vector of StudentId
*/
vector<int> getCourseStudents(const int& cid);

/*
   Returns total number of active enrollments.
   - Output: size_t (total number of (student,course) pairs)
*/

size_t totalEnrollments();

// -------------------- FILE HANDLING --------------------
// Load all students and enrollments from file
void loadStudentData();
// Save all students and enrollments to file
void saveStudentData();

#endif // STUDENT_SCHEDULE_H
