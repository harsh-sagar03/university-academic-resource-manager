#include "course_management.h"
#include <iostream>
#include <algorithm>
using namespace std;

/*
   INTERNAL STORAGE
*/
static vector<Course> courseList;

// Default constructor
Course::Course() : id(0), name(""), credits(0) {}


// ======================================================
//                  FUNCTION IMPLEMENTATIONS
// ======================================================

void addCourse(const Course& c) {
    // Prevent duplicate ID
    for (const auto &x : courseList) {
        if (x.getId() == c.getId()) {
            cout << "Course with ID " << c.getId() << " already exists.\n";
            return;
        }
    }
    courseList.push_back(c);
}

void removeCourse(int id) {
    auto it = remove_if(courseList.begin(), courseList.end(),
        [id](const Course& c){ return c.getId() == id; });

    if (it == courseList.end()) {
        cout << "Course ID " << id << " not found.\n";
        return;
    }
    courseList.erase(it, courseList.end());
}

Course* searchCourseById(int id) {
    for (auto &c : courseList)
        if (c.getId() == id)
            return &c;
    return nullptr;
}

Course* searchCourseByName(const string& name) {
    for (auto &c : courseList)
        if (c.getName() == name)
            return &c;
    return nullptr;
}

void updateCourseCredits(int id, int credits) {
    Course* c = searchCourseById(id);
    if (!c) {
        cout << "Course ID " << id << " not found.\n";
        return;
    }
    c->setCredits(credits);
}

void sortCoursesByName() {
    sort(courseList.begin(), courseList.end(),
        [](const Course& a, const Course& b){
            return a.getName() < b.getName();
        });
}

void sortCoursesByCredits() {
    sort(courseList.begin(), courseList.end(),
        [](const Course& a, const Course& b){
            return a.getCredits() < b.getCredits();
        });
}

void displayAllCourses() {
    if (courseList.empty()) {
        cout << "No courses available.\n";
        return;
    }

    cout << "ID\tName\t\tCredits\n";
    cout << "------------------------------------\n";

    for (const auto &c : courseList) {
        cout << c.getId() << "\t" 
             << c.getName() << "\t\t" 
             << c.getCredits() << "\n";
    }
}
