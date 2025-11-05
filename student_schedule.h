#ifndef STUDENT_SCHEDULE_H
#define STUDENT_SCHEDULE_H
#include <string>
#include <vector>
#using namespace std;
/*
=========================================================
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
=========================================================
*/

// -------------------- TYPEDEFS --------------------
/*
   Defining StudentId and CourseId as aliases for int.
   This makes it easy to change type later if needed.
*/
using StudentId = int;
using CourseId  = int;

// -------------------- STRUCT DEFINITIONS --------------------
/*
   Represents a student with:
   - id   : Unique integer identifier
   - name : Student's full name
*/
class Student {
private:
    StudentId id;
    string name;
    String department;
    // (Optionally: year etc. can be added later)
// Constructors
public:
// Default Constructor
Student();

// Parameterized Constructor
Student(StudentID id,string name,String department){
    this->id=id;
    this->name=name;
    thid->department=department;   
}
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
void removeStudent(const StudentId& id); //removeStudent: must also clean up all their course enrollments.

/*
   Enrolls a student in a course.
   - Input: StudentId, CourseId
*/
void enrollStudentInCourse(const StudentId& sid, const CourseId& cid);

/*
   Drops a student from a specific course.
   - Input: StudentId, CourseId
*/
void dropStudentFromCourse(const StudentId& sid, const CourseId& cid);

/*
   Displays the full schedule (list of courses) for a student.
   - Input: StudentId
*/
void displayStudentSchedule(const StudentId& sid);

/*
   Checks if a student is enrolled in a given course.
   - Input: StudentId, CourseId
   - Output: true if enrolled, false otherwise
*/
bool isStudentEnrolledInCourse(const StudentId& sid, const CourseId& cid);

/*
   Gets all courses that a student is enrolled in.
   - Input: StudentId
   - Output: vector of CourseId
*/
vector<CourseId> getStudentCourses(const StudentId& sid);

/*
   Gets all students who are enrolled in a given course.
   - Input: CourseId
   - Output: vector of StudentId
*/
vector<StudentId> getCourseStudents(const CourseId& cid);

/*
   Returns total number of active enrollments.
   - Output: size_t (total number of (student,course) pairs)
*/
size_t totalEnrollments();

#endif // STUDENT_SCHEDULE_H
