#ifndef COURSE_MANAGEMENT_H
#define COURSE_MANAGEMENT_H

#include <string>
#include <vector>
using namespace std;

/*
    COURSE MANAGEMENT MODULE (Part A)
    ---------------------------------
    This module provides functionalities for managing
    university courses. It supports adding, removing,
    searching, updating, sorting, and displaying courses.

    How to use:
    - Include this header in main.cpp (or any other file).
    - Implement the functions in course_management.cpp.
    - Do NOT write the full logic here (only declarations).
*/

class Course {
private:
    int id;
    string name;
    int credits;
public:

Course();

Course(int id,string name, int credits){
    this->id = id;
    this->name = name;
    this->credits = credits;
}
 // -------- GETTERS --------
int getId() const { return id; }
string getName() const { return name; }
int getCredits() const { return credits; }
// -------- SETTERS --------
void setCredits(int c) { credits = c; }
};

void addCourse(const Course& c);
void removeCourse(int id);

/*
   Searches for a course by its id.
   - Input: int id
   - Output: Pointer to Course (nullptr if not found)
*/
Course* searchCourseById(int id);

/*
   Searches for a course by its name.
   - Input: string name
   - Output: Pointer to Course (nullptr if not found)
*/
Course* searchCourseByName(const string& name);

/*
   Updates the credit value of a course.
   - Input: id (course id), credits (new credit value)
   - Effect: Modifies course if found
*/
void updateCourseCredits(int id, int credits);

/*
   Sorts the course list alphabetically by name.
   - Effect: Reorders internal list
*/
void sortCoursesByName(); //!!!->>Sorting functions don’t return anything → they reorder the internal container.

/*
   Sorts the course list by credits (ascending).
   - Effect: Reorders internal list
*/
void sortCoursesByCredits();

/*
   Displays all courses in a tabular format.
   - Effect: Prints id, name, and credits to console
*/
void displayAllCourses();

void loadCourseData();

// Saves all current courses into courses.txt
void saveCourseData();

#endif 
