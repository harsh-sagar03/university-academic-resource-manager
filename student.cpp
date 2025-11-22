#include "student_schedule.h"
#include <iostream>
#include <algorithm>
using namespace std;

/*
    INTERNAL STORAGE
*/
static vector<Student> studentList;
static vector<pair<int,int>> enrollments;  // (studentId, courseId)


// ------------------ Student Default Constructor ------------------
Student::Student() : id(0), name(""), department("") {}


// ------------------ Helper function: search by ID ------------------
static Student* searchStudentById(int id) {
    for (auto &s : studentList)
        if (s.getId() == id)
            return &s;
    return nullptr;
}


// ======================================================
//                  FUNCTION IMPLEMENTATIONS
// ======================================================

void addStudent(const Student& s) {
    // Prevent duplicate student ID
    for (auto &x : studentList) {
        if (x.getId() == s.getId()) {
            cout << "Student ID " << s.getId() << " already exists.\n";
            return;
        }
    }
    studentList.push_back(s);
}

void removeStudent(const int& id) {
    bool found = false;

    // Remove student
    auto it = remove_if(studentList.begin(), studentList.end(),
        [id, &found](const Student& s){
            if (s.getId() == id) {
                found = true;
                return true;
            }
            return false;
        });

    if (!found) {
        cout << "Student ID " << id << " not found.\n";
        return;
    }

    studentList.erase(it, studentList.end());

    // Remove all enrollments of this student
    enrollments.erase(
        remove_if(enrollments.begin(), enrollments.end(),
            [id](const pair<int,int>& p){
                return p.first == id;
            }),
        enrollments.end()
    );
}

void enrollStudentInCourse(const int& sid, const int& cid) {
    if (!searchStudentById(sid)) {
        cout << "Student " << sid << " does not exist.\n";
        return;
    }

    // Prevent duplicate enrollment
    for (auto &p : enrollments)
        if (p.first == sid && p.second == cid) {
            cout << "Student already enrolled in course.\n";
            return;
        }

    enrollments.push_back({sid, cid});
}

void dropStudentFromCourse(const int& sid, const int& cid) {
    auto it = remove_if(enrollments.begin(), enrollments.end(),
        [sid, cid](const pair<int,int>& p){
            return (p.first == sid && p.second == cid);
        });

    if (it == enrollments.end()) {
        cout << "Enrollment not found.\n";
        return;
    }

    enrollments.erase(it, enrollments.end());
}

bool isStudentEnrolledInCourse(const int& sid, const int& cid) {
    for (auto &p : enrollments)
        if (p.first == sid && p.second == cid)
            return true;
    return false;
}

vector<int> getStudentCourses(const int& sid) {
    vector<int> list;
    for (auto &p : enrollments)
        if (p.first == sid)
            list.push_back(p.second);
    return list;
}

vector<int> getCourseStudents(const int& cid) {
    vector<int> list;
    for (auto &p : enrollments)
        if (p.second == cid)
            list.push_back(p.first);
    return list;
}

size_t totalEnrollments() {
    return enrollments.size();
}

void displayStudentSchedule(const int& sid) {
    Student* s = searchStudentById(sid);
    if (!s) {
        cout << "Student ID " << sid << " not found.\n";
        return;
    }

    cout << "\nSchedule for Student " << sid 
         << " (" << s->getName() << ")\n";
    cout << "------------------------------------\n";

    vector<int> courses = getStudentCourses(sid);

    if (courses.empty()) {
        cout << "No courses enrolled.\n";
        return;
    }

    for (int cid : courses)
        cout << "- Course ID: " << cid << "\n";
}
