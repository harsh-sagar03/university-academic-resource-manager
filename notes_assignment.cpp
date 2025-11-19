#include "notes_assignment.h"
#include<iostream>
using namespace std;

queue<Assignment> assignmentQueue;
stack<Note> notesStack;

// ---------------- ASSIGNMENT QUEUE FUNCTIONS ----------------

// Add a new assignment to the queue.
void addAssignment(const Assignment& a) {
    assignmentQueue.push(a);
}

// View the next assignment without removing it.
Assignment* peekNextAssignment() {
    if (assignmentQueue.empty()) {
        cout << "No assignments waiting.\n";
        return nullptr;
    }
    return &assignmentQueue.front();
}

// Remove the next assignment from the queue.
void completeNextAssignment() {
    if (assignmentQueue.empty()) {
        cout << "No assignments to complete.\n";
        return;
    }
    assignmentQueue.pop();
}

// Check if the assignment list is empty.
bool isAssignmentQueueEmpty() {
    return assignmentQueue.empty();
}

// Display all assignments in order (non-destructive).
void displayAllAssignments() {
    if (assignmentQueue.empty()) {
        cout << "No assignments available.\n";
        return;
    }

    queue<Assignment> temp = assignmentQueue;

    cout << "Assignments (FIFO order):\n";
    while (!temp.empty()) {
        Assignment a = temp.front();
        temp.pop();
        cout << "- " << a.title << " (Due: " << a.dueDate << ")\n";
    }
}


// ---------------- NOTES STACK FUNCTIONS ----------------

// Push new note onto the stack.
void addNote(const Note& n) {
    notesStack.push(n);
}

// Look at the latest note.
Note* viewLatestNote() {
    if (notesStack.empty()) {
        cout << "No notes added yet.\n";
        return nullptr;
    }
    return &notesStack.top();
}

// Remove the latest note.
void removeLatestNote() {
    if (notesStack.empty()) {
        cout << "No notes to remove.\n";
        return;
    }
    notesStack.pop();
}

// Check if notes stack is empty.
bool isNotesEmpty() {
    return notesStack.empty();
}

// Display all notes (non-destructive).
void displayAllNotes() {
    if (notesStack.empty()) {
        cout << "No notes stored.\n";
        return;
    }

    stack<Note> temp = notesStack;

    cout << "Notes (LIFO order):\n";
    while (!temp.empty()) {
        Note n = temp.top();
        temp.pop();
        cout << "- " << n.text << "\n";
    }
}