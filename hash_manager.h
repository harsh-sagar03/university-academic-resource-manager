#ifndef HASH_MANAGER_H
#define HASH_MANAGER_H

#include <string>
#include <unordered_map>
#include <cstddef> // for size_t
#include <iostream>
#include <vector>

using namespace std;

/*
    HASH MANAGER MODULE (Part D)
    ----------------------------
    Provides fast access to Courses, Students, and 
    Assignments using separate hash tables. 
    Uses std::unordered_map for O(1) average lookups.

    Features:
    - Insert, find, remove entities (Course, Student, Assignment)
    - Check existence (contains)
    - Display hash table statistics (load factor, collisions)
    - Clear all hash tables

    How to use:
    - Include this header in main.cpp.
    - Implement the functions in hash_manager.cpp.
*/

using CourseId  = int;
using StudentId = int;

/*
   Course entity
*/
struct HashCourse {
    CourseId id;
    string name;
    int credits;
};

/*
   Student entity
*/
struct HashStudent {
    StudentId id;
    string name;
};

/*
   Assignment entity
*/
struct HashAssignment {
    string id;     
    string title;
    string dueDate;
    bool completed = false;
};

// -------------------- COURSE HASH FUNCTIONS --------------------
void insertCourse(const HashCourse& c);
HashCourse* findCourseById(const CourseId& id);
void removeCourseById(const CourseId& id);
bool containsCourse(const CourseId& id);

// -------------------- STUDENT HASH FUNCTIONS --------------------
void insertStudent(const HashStudent& s);
HashStudent* findStudentById(const StudentId& id);
void removeStudentById(const StudentId& id);
bool containsStudent(const StudentId& id);

// -------------------- ASSIGNMENT HASH FUNCTIONS --------------------
void insertAssignment(const HashAssignment& a);
HashAssignment* findAssignmentById(const string& id);
void removeAssignmentById(const string& id);
bool containsAssignment(const string& id);


void displayHashTableStats();

void clearHashTables();

#endif // HASH_MANAGER_H