#include "course_management.h"
#include "student_schedule.h"
#include <iostream>
#include <vector>
using namespace std;

/*
    INTERNAL STORAGE
*/
static vector<Student> studentList;
static vector<pair<int,int>> enrollments;   // (studentId, courseId)


// ------------------ Student Default Constructor ------------------
Student::Student() : id(0), name(""), department("") {}


// ------------------ Helper function: search by ID ------------------
static Student* searchStudentById(int id) {
    for (int i = 0; i < (int)studentList.size(); i++) {
        if (studentList[i].getId() == id)
            return &studentList[i];
    }
    return NULL;
}


// ======================================================
//               FUNCTION IMPLEMENTATIONS
// ======================================================

void addStudent(const Student &s) {
    // Prevent duplicate ID
    for (int i = 0; i < (int)studentList.size(); i++) {
        if (studentList[i].getId() == s.getId()) {
            cout << "Student ID " << s.getId() << " already exists.\n";
            return;
        }
    }
    studentList.push_back(s);
    saveStudentData();
}

void removeStudent(const int &id) {
    bool found = false;

    // remove student
    for (int i = 0; i < (int)studentList.size(); i++) {
        if (studentList[i].getId() == id) {
            studentList.erase(studentList.begin() + i);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student ID " << id << " not found.\n";
        return;
    }

    // remove enrollments
    for (int i = 0; i < (int)enrollments.size(); ) {
        if (enrollments[i].first == id)
            enrollments.erase(enrollments.begin() + i);
        else
            i++;
    }
}

void enrollStudentInCourse(const int &sid, const int &cid) {
    if (searchStudentById(sid) == NULL) {
        cout << "Student " << sid << " does not exist.\n";
        return;
    }

    // check duplicate
    for (int i = 0; i < (int)enrollments.size(); i++) {
        if (enrollments[i].first == sid && enrollments[i].second == cid) {
            cout << "Student already enrolled in this course.\n";
            return;
        }
    }

    enrollments.push_back(make_pair(sid, cid));
}

void dropStudentFromCourse(const int &sid, const int &cid) {
    bool removed = false;

    for (int i = 0; i < (int)enrollments.size(); i++) {
        if (enrollments[i].first == sid && enrollments[i].second == cid) {
            enrollments.erase(enrollments.begin() + i);
            removed = true;
            break;
        }
    }

    if (!removed)
        cout << "Enrollment not found.\n";
}

bool isStudentEnrolledInCourse(const int &sid, const int &cid) {
    for (int i = 0; i < (int)enrollments.size(); i++) {
        if (enrollments[i].first == sid && enrollments[i].second == cid)
            return true;
    }
    return false;
}

vector<int> getStudentCourses(const int &sid) {
    vector<int> list;

    for (int i = 0; i < (int)enrollments.size(); i++) {
        if (enrollments[i].first == sid)
            list.push_back(enrollments[i].second);
    }
    return list;
}

vector<int> getCourseStudents(const int &cid) {
    vector<int> list;

    for (int i = 0; i < (int)enrollments.size(); i++) {
        if (enrollments[i].second == cid)
            list.push_back(enrollments[i].first);
    }
    return list;
}

size_t totalEnrollments() {
    return enrollments.size();
}

void displayStudentSchedule(const int &sid) {
    Student *s = searchStudentById(sid);

    if (s == NULL) {
        cout << "Student ID " << sid << " not found.\n";
        return;
    }

    cout << "\nSchedule for Student " << sid 
         << " (" << s->getName() << ")\n";
    cout << "\n";

    vector<int> courses = getStudentCourses(sid);

    if (courses.empty()) {
        cout << "No courses enrolled.\n";
        return;
    }

    for (int i = 0; i < (int)courses.size(); i++) {
        cout << "- Course ID: " << courses[i] << "\n";
    }
}
