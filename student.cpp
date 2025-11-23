#include "course_management.h"
#include "student_schedule.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
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
    saveEnrollments();
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

    saveEnrollments();
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

void saveStudentData() {
    ofstream out("students.txt");
    if(!out) return;

    for(const auto &s : studentList) {
        out << s.getId() << "," 
            << s.getName() << "," 
            << s.getDepartment() << "\n";
    }
    out.close();
}

void loadStudentData() {
    studentList.clear();

    ifstream in("students.txt");
    if(!in) return;

    string line;
    while(getline(in, line)) {
        if(line.empty()) continue;

        stringstream ss(line);
        string idStr, name, dept;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, dept, ',');

        if(idStr.empty() || name.empty() || dept.empty())
            continue;

        int id = stoi(idStr);
        Student s;
        s.setId(id);
        s.setName(name);
        s.setDepartment(dept);

        studentList.push_back(s);
    }

    in.close();
    loadEnrollments();
}

void saveEnrollments() {
    ofstream out("enrollments.txt");
    if (!out) return;

    for (const auto &p : enrollments) {
        out << p.first << "," << p.second << "\n";
    }
    out.close();
}

void loadEnrollments() {
    enrollments.clear();

    ifstream in("enrollments.txt");
    if (!in) return;

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string sidStr, cidStr;

        getline(ss, sidStr, ',');
        getline(ss, cidStr, ',');

        if (sidStr.empty() || cidStr.empty()) continue;

        int sid = stoi(sidStr);
        int cid = stoi(cidStr);

        enrollments.push_back(make_pair(sid, cid));
    }

    in.close();
}
