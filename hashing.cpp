#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct HashCourse {
    int id;
    string name;
    int credits;
};

// -------------------- GLOBAL HASH TABLE --------------------
unordered_map<int, HashCourse> courseTable; //Store and access courses by ID quickly


// Insert a new course
void insertCourse(const HashCourse& c) {
    courseTable[c.id] = c;
}

// Find a course by ID
HashCourse* findCourseById(const int& id) {
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



#include <iostream>
#include <string>
#include <unordered_map>

// -------------------- STUDENT STRUCT --------------------
struct HashStudent {
    int id;
    string name;
};

// -------------------- GLOBAL HASH TABLE --------------------
unordered_map<int, HashStudent> studentTable;

// -------------------- STUDENT FUNCTIONS --------------------

// Insert a new student
void insertStudent(const HashStudent& s) {
    studentTable[s.id] = s;
}

// Find a student by ID
HashStudent* findStudentById(const int& id) {
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



#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// -------------------- ASSIGNMENT STRUCT --------------------
struct HashAssignment {
    string id;
    string title;
    string dueDate;
    bool completed;
};

// -------------------- GLOBAL HASH TABLE --------------------
unordered_map<string, HashAssignment> assignmentTable;

// -------------------- ASSIGNMENT FUNCTIONS --------------------

// Insert a new assignment
void insertAssignment(const HashAssignment& a) {
    assignmentTable[a.id] = a;
}

// Find an assignment by ID
HashAssignment* findAssignmentById(const string& id) {
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

/* -------------------- HASH TABLE STATS -------------------- */
void displayHashTableStats() {
    cout << "Courses stored: " << courseTable.size() << endl;
    cout << "Students stored: " << studentTable.size() << endl;
    cout << "Assignments stored: " << assignmentTable.size() << endl;
}

/* ===================== FILE HANDLING ===================== */

#include <fstream>

// ---------- Load all hash tables ----------
void loadHashData() {

    // --- Load Courses ---
    courseTable.clear();
    ifstream fc("hash_courses.txt");
    if (fc.is_open()) {
        string line;
        while (getline(fc, line)) {
            if (line.empty()) continue;

            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            if (p1 == string::npos || p2 == string::npos) continue;

            HashCourse c;
            c.id = stoi(line.substr(0, p1));
            c.name = line.substr(p1 + 1, p2 - p1 - 1);
            c.credits = stoi(line.substr(p2 + 1));

            courseTable[c.id] = c;
        }
        fc.close();
    }

    // --- Load Students ---
    studentTable.clear();
    ifstream fs("hash_students.txt");
    if (fs.is_open()) {
        string line;
        while (getline(fs, line)) {
            if (line.empty()) continue;

            size_t p = line.find('|');
            if (p == string::npos) continue;

            HashStudent s;
            s.id = stoi(line.substr(0, p));
            s.name = line.substr(p + 1);

            studentTable[s.id] = s;
        }
        fs.close();
    }

    // --- Load Assignments ---
    assignmentTable.clear();
    ifstream fa("hash_assignments.txt");
    if (fa.is_open()) {
        string line;
        while (getline(fa, line)) {
            if (line.empty()) continue;

            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);
            if (p1 == string::npos || p2 == string::npos || p3 == string::npos) continue;

            HashAssignment a;
            a.id = line.substr(0, p1);
            a.title = line.substr(p1 + 1, p2 - p1 - 1);
            a.dueDate = line.substr(p2 + 1, p3 - p2 - 1);
            a.completed = stoi(line.substr(p3 + 1));

            assignmentTable[a.id] = a;
        }
        fa.close();
    }
}

// ---------- Save all hash tables ----------
void saveHashData() {

    // --- Save Courses ---
    ofstream fc("hash_courses.txt");
    if (fc.is_open()) {
        for (auto &pair : courseTable) {
            const HashCourse &c = pair.second;
            fc << c.id << "|" << c.name << "|" << c.credits << "\n";
        }
        fc.close();
    }

    // --- Save Students ---
    ofstream fs("hash_students.txt");
    if (fs.is_open()) {
        for (auto &pair : studentTable) {
            const HashStudent &s = pair.second;
            fs << s.id << "|" << s.name << "\n";
        }
        fs.close();
    }

    // --- Save Assignments ---
    ofstream fa("hash_assignments.txt");
    if (fa.is_open()) {
        for (auto &pair : assignmentTable) {
            const HashAssignment &a = pair.second;
            fa << a.id << "|" << a.title << "|" 
               << a.dueDate << "|" << a.completed << "\n";
        }
        fa.close();
    }
}
