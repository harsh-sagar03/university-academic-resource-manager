#include <iostream>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
#include "course_management.h"
#include "notes_assignment.h"
#include "hash_manager.h"
#include "student_schedule.h"
#include "graph.h"

extern Graph globalGraph;

void loadCourseData();
void saveCourseData();
void loadStudentData();
void saveStudentData();
void loadNotesData();
void saveNotesData();
void loadHashData();
void saveHashData();
void pause(bool doIgnore);
void graphMenu() {
    cout << "\n--- SEMESTER PLANNER (GRAPH / TOPOLOGICAL SORT) ---\n";

    int n;
    cout << "Enter number of courses (nodes): ";
    cin >> n;

    Graph g(n);

    int e;
    cout << "Enter number of prerequisite relations: ";
    cin >> e;

    cout << "Enter edges as: prereq_course dependent_course\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int choice;
    cout << "\n1. Show Adjacency List\n";
    cout << "2. Topological Sort (Course Order)\n";
    cout << "3. Semester-wise Plan\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) g.printGraph();
    else if (choice == 2) g.topologicalSort();
    else if (choice == 3) g.semesterPlan();
    else cout << "Invalid option.\n";

    pause(false);
}

using namespace std;

void printSlow(const string& text, int delay = 2000) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::microseconds(delay));
    }
}

void welcomeScreen() {
    cout << "\033[1;36m";
    printSlow("============================================\n", 2000);
    printSlow("     UNIVERSITY ACADEMIC RESOURCE MANAGER    \n", 2000);
    printSlow("============================================\n", 2000);
    cout << "\033[0m";

    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\033[1;32mLoading";
    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "." << flush;
    }
    cout << "\033[0m\n\n";
}

void pause(bool doIgnore = true) {
    if (doIgnore) cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\033[1;33mPress Enter to continue...\033[0m";
    cin.get();
}

void courseMenu() {
    int c;
    bool doIgnore = true;
    cout << "\n--- COURSE MANAGEMENT (ARRAY + SORTING) ---\n";
    cout << "1. Add Course\n";
    cout << "2. Remove Course\n";
    cout << "3. Search by ID\n";
    cout << "4. Search by Name\n";
    cout << "5. Update Credits\n";
    cout << "6. Sort by Name\n";
    cout << "7. Sort by Credits\n";
    cout << "8. Display All\n";
    cout << "Enter choice: ";
    cin >> c;

    if (c == 1) {
        int id, cr;
        string name;
        cout << "ID: "; cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, name);
        cout << "Credits: "; cin >> cr;
        addCourse(Course(id, name, cr));
    }
    else if (c == 2) {
        int id; cout << "ID: "; cin >> id; removeCourse(id);
    }
    else if (c == 3) {
        int id; cout << "ID: "; cin >> id; 
        Course* res = searchCourseById(id);
        if (res) cout << "Found: " << res->getName() << " (" << res->getCredits() << " credits)\n";
        else cout << "Course not found.\n";
    }
    else if (c == 4) {
        string n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, n);
        Course* res = searchCourseByName(n);
        if (res) cout << "Found: ID " << res->getId() << " (" << res->getCredits() << " credits)\n";
        else cout << "Course not found.\n";
        doIgnore = false;
    }
    else if (c == 5) {
        int id, cr; cout << "ID: "; cin >> id; cout << "New credits: "; cin >> cr; updateCourseCredits(id, cr);
    }
    else if (c == 6) sortCoursesByName();
    else if (c == 7) sortCoursesByCredits();
    else if (c == 8) displayAllCourses();

    pause(doIgnore);
}

void notesMenu() {
    int n;
    bool doIgnore = true;
    cout << "\n--- NOTES & ASSIGNMENTS (STACK) ---\n";
    cout << "1. Add Note\n";
    cout << "2. Pop Last Note\n";
    cout << "3. Peek Note\n";
    cout << "4. Display All Notes\n";
    cout << "Enter choice: ";
    cin >> n;

    if (n == 1) {
        string t;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Title: ";
        getline(cin, t);
        pushNote(t);
        doIgnore = false;
    }
    else if (n == 2) popNote();
    else if (n == 3) peekNote();
    else if (n == 4) displayAllNotes();

    pause(doIgnore);
}

void hashMenu() {
    int h;
    bool doIgnore = true;
    cout << "\n--- HASH TABLE MANAGER (HASHING) ---\n";
    cout << "1. Insert Student\n";
    cout << "2. Find Student\n";
    cout << "3. Remove Student\n";
    cout << "4. Table Stats\n";
    cout << "Enter choice: ";
    cin >> h;

    if (h == 1) {
        HashStudent s;
        cout << "ID: "; cin >> s.id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, s.name);
        insertStudent(s);
        doIgnore = false;
    }
    else if (h == 2) {
        int id; cout << "ID: "; cin >> id;
        HashStudent* s = findStudentById(id);
        if (s) cout << "Found: " << s->name << "\n";
        else cout << "Not found!\n";
    }
    else if (h == 3) {
        int id; cout << "ID: "; cin >> id; removeStudentById(id);
    }
    else if (h == 4) displayHashTableStats();

    pause(doIgnore);
}

void scheduleMenu() {
    int s;
    bool doIgnore = true;
    cout << "\n--- STUDENT SCHEDULE (LINKED LIST) ---\n";
    cout << "1. Add Student\n";
    cout << "2. Remove Student\n";
    cout << "3. Enroll Student in Course\n";
    cout << "4. Drop Student from Course\n";
    cout << "5. Display Student Schedule\n";
    cout << "Enter choice: ";
    cin >> s;

    if (s == 1) {
        int id;
        string name, dept;
        cout << "Student ID: "; cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, name);
        cout << "Department: ";
        getline(cin, dept);
        addStudent(Student(id, name, dept));
        doIgnore = false;
    }
    else if (s == 2) {
        int id;
        cout << "Student ID to remove: "; cin >> id;
        removeStudent(id);
    }
    else if (s == 3) {
        int sid, cid;
        cout << "Student ID: "; cin >> sid;
        cout << "Course ID: "; cin >> cid;
        enrollStudentInCourse(sid, cid);
    }
    else if (s == 4) {
        int sid, cid;
        cout << "Student ID: "; cin >> sid;
        cout << "Course ID: "; cin >> cid;
        dropStudentFromCourse(sid, cid);
    }
    else if (s == 5) {
        int sid;
        cout << "Student ID: "; cin >> sid;
        displayStudentSchedule(sid);
    }

    pause(doIgnore);
}

int main() {
    loadCourseData();
    loadStudentData();
    loadNotesData();
    globalGraph.loadFromFile();
    loadHashData();
    welcomeScreen();
    int choice;

    while (true) {
        cout << "\n\033[1;34m====== UNIVERSITY RESOURCE MANAGER ======\033[0m\n";
        cout << "1. Course Management      (Arrays + Sorting)\n";
        cout << "2. Notes & Assignments    (Stack Implementation)\n";
        cout << "3. Hash Table Manager     (Hashing + Key Lookup)\n";
        cout << "4. Student Schedule       (Linked List Structure)\n";
        cout << "5. Semester Planner (Graph + Topological Sort)\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) courseMenu();
        else if (choice == 2) notesMenu();
        else if (choice == 3) hashMenu();
        else if (choice == 4) scheduleMenu();
        else if (choice == 5) graphMenu();
        else if (choice == 6) { cout << "Goodbye!\n"; break; }
        else cout << "Invalid choice!\n";
    }

    saveCourseData();
    saveStudentData();
    saveNotesData();
    globalGraph.saveToFile();
    saveHashData();
    return 0;
}