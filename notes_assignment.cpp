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

void pushNote(const string& text) {
    Note n;
    n.text = text;
    notesStack.push(n);
}

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

void popNote() {
    if (notesStack.empty()) {
        cout << "No notes to pop.\n";
        return;
    }
    notesStack.pop();
}

void peekNote() {
    if (notesStack.empty()) {
        cout << "No notes available.\n";
        return;
    }
    cout << "Top Note: " << notesStack.top().text << "\n";
}

/* ===================== FILE HANDLING ===================== */

#include <fstream>

// ---------- Load Notes & Assignments ----------
void loadNotesData() {

    // Clear current data
    while (!notesStack.empty()) notesStack.pop();
    while (!assignmentQueue.empty()) assignmentQueue.pop();

    ifstream fin("notes.txt");
    if (!fin.is_open()) return;

    string line;
    bool readingNotes = true;

    while (getline(fin, line)) {

        if (line == "#ASSIGNMENTS") {
            readingNotes = false;
            continue;
        }

        if (line.empty()) continue;

        if (readingNotes) {
            // Each line is a note
            Note n;
            n.text = line;
            notesStack.push(n);
        } else {
            // Assignment format: title|dueDate
            size_t p = line.find('|');
            if (p == string::npos) continue;

            string title = line.substr(0, p);
            string due = line.substr(p + 1);

            Assignment a;
            a.title = title;
            a.dueDate = due;

            assignmentQueue.push(a);
        }
    }

    fin.close();
}

// ---------- Save Notes & Assignments ----------
void saveNotesData() {

    ofstream fout("notes.txt");
    if (!fout.is_open()) return;

    // Save notes (top of stack last)
    stack<Note> tempNotes = notesStack;
    stack<Note> reversed;

    while (!tempNotes.empty()) {
        reversed.push(tempNotes.top());
        tempNotes.pop();
    }

    while (!reversed.empty()) {
        fout << reversed.top().text << "\n";
        reversed.pop();
    }

    fout << "#ASSIGNMENTS\n";

    // Save assignments
    queue<Assignment> temp = assignmentQueue;

    while (!temp.empty()) {
        Assignment a = temp.front();
        temp.pop();
        fout << a.title << "|" << a.dueDate << "\n";
    }

    fout.close();
}