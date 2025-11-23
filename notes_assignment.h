#ifndef NOTES_ASSIGNMENTS_H
#define NOTES_ASSIGNMENTS_H

#include <string>
#include <queue>
#include <stack>
#include <cstddef> // for size_t
using namespace std;
/*

    ASSIGNMENT & NOTES MODULE (Part C)
    ----------------------------------
    This module manages:
    - Assignments (using a queue → FIFO order)
    - Notes (using a stack → LIFO order)

    Assignments:
        - Added at the back (enqueue)
        - Processed from the front (dequeue)
        - Can be marked as complete

    Notes:
        - Added on top (push)
        - Removed from top (pop)
        - Top note can be viewed (peek)

    How to use:
    - Include this header in main.cpp (or any file).
    - Implement the functions in notes_assignments.cpp.

*/

// -------------------- STRUCT DEFINITIONS --------------------
/*
   Represents an assignment with:
   - id       : Unique string identifier (e.g., "A101")
   - title    : Short description/title
   - dueDate  : Optional (string format, e.g., "2025-10-05")
   - status   : true if completed, false otherwise
*/
struct Assignment {
    std::string id;
    std::string title;
    std::string dueDate;
    bool completed = false;
};
struct Note {
    string text;
};
// -------------------- ASSIGNMENT FUNCTIONS --------------------
/*
   Adds a new assignment into the pending queue.
   - Input: const reference to Assignment object
*/
void addAssignment(const Assignment& a);

/*
   Returns the next assignment in the queue (front).
   - Output: Assignment (copy)
   - Note: This should also remove it from the queue
*/
Assignment getNextAssignment();

/*
   Marks an assignment as completed by id.
   - Input: assignmentId (string)
   - Output: true if found and marked, false otherwise
*/
bool completeAssignment(const string& assignmentId);

/*
   Displays all pending assignments in queue order.
*/
void displayPendingAssignments();

/*
   Checks if there are any pending assignments.
   - Output: true if queue is non-empty
*/
bool hasPendingAssignments();

/*
   Returns total number of assignments currently in system.
   - Output: size_t
*/
size_t totalAssignments();

// -------------------- NOTE FUNCTIONS --------------------
/*
   Pushes a note onto the stack.
   - Input: note (string)
*/
void pushNote(const string& note);

/*
   Pops (removes) the most recent note from the stack.
   - Output: string (the popped note)
   - Note: should handle empty stack safely
*/
void popNote();

/*
   Returns the top note without removing it.
   - Output: string (the top note)
*/
void peekNote();

/*
   Displays all notes in stack order (top to bottom).
*/
void displayAllNotes();

/*
   Returns total number of notes currently in stack.
   - Output: size_t
*/
size_t totalNotes();

// -------------------- FILE HANDLING --------------------
// Load all notes & assignments from file
void loadNotesData();
// Save all notes & assignments to file
void saveNotesData();

#endif // NOTES_ASSIGNMENTS_H