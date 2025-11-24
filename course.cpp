#include "course_management.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
   INTERNAL STORAGE
*/
static vector<Course> courseList;

Course::Course() : id(0), name(""), credits(0) {}

//               FUNCTION DEFINITIONS
void addCourse(const Course &c) {
    // Check duplicate
    for (int i = 0; i < (int)courseList.size(); i++) {
        if (courseList[i].getId() == c.getId()) {
            cout << "Course with ID " << c.getId() << " already exists.\n";
            return;
        }
    }
    courseList.push_back(c);
}

/* ===================== FILE HANDLING ===================== */

#include <fstream>

void loadCourseData() {
    courseList.clear();
    ifstream fin("courses.txt");
    if (!fin.is_open()) return;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);

        if (p1 == string::npos || p2 == string::npos) continue;

        int id = stoi(line.substr(0, p1));
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        int credits = stoi(line.substr(p2 + 1));

        courseList.push_back(Course(id, name, credits));
    }

    fin.close();
}

void saveCourseData() {
    ofstream fout("courses.txt");
    if (!fout.is_open()) return;

    for (const auto &c : courseList) {
        fout << c.getId() << "|"
             << c.getName() << "|"
             << c.getCredits() << "\n";
    }

    fout.close();
}

void removeCourse(int id) {
    bool found = false;

    for (int i = 0; i < (int)courseList.size(); i++) {
        if (courseList[i].getId() == id) {
            courseList.erase(courseList.begin() + i);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Course ID " << id << " not found.\n";
    }
}

Course* searchCourseById(int id) {
    for (int i = 0; i < (int)courseList.size(); i++) {
        if (courseList[i].getId() == id)
            return &courseList[i];
    }
    return NULL;
}

Course* searchCourseByName(const string &name) {
    for (int i = 0; i < (int)courseList.size(); i++) {
        if (courseList[i].getName() == name)
            return &courseList[i];
    }
    return NULL;
}

void updateCourseCredits(int id, int credits) {
    Course* c = searchCourseById(id);

    if (c == NULL) {
        cout << "Course ID " << id << " not found.\n";
        return;
    }

    c->setCredits(credits);
}

void sortCoursesByName() {
    for (int i = 0; i < (int)courseList.size(); i++) {
        for (int j = i + 1; j < (int)courseList.size(); j++) {
            if (courseList[j].getName() < courseList[i].getName()) {
                Course temp = courseList[i];
                courseList[i] = courseList[j];
                courseList[j] = temp;
            }
        }
    }
}

void sortCoursesByCredits() {
    for (int i = 0; i < (int)courseList.size(); i++) {
        for (int j = i + 1; j < (int)courseList.size(); j++) {
            if (courseList[j].getCredits() < courseList[i].getCredits()) {
                Course temp = courseList[i];
                courseList[i] = courseList[j];
                courseList[j] = temp;
            }
        }
    }
}

void displayAllCourses() {
    if (courseList.empty()) {
        cout << "No courses available.\n";
        return;
    }

    cout << "ID\tName\t\tCredits\n";
    cout << "\n";

    for (int i = 0; i < (int)courseList.size(); i++) {
        cout << courseList[i].getId() << "\t"
             << courseList[i].getName() << "\t\t"
             << courseList[i].getCredits() << "\n";
    }
}
