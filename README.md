# university-academic-resource-manager
# Overview

The Academic Resource Manager is a modular C++ project designed to manage and organize university-level academic data such as departments, courses, resources, and student records. It demonstrates the practical use of core data structures including arrays, linked lists, stacks, queues, multi-lists, graphs, and hash tables. All modules are implemented in separate .h and .cpp files, with persistent data stored in .txt files. 

The system models an academic ecosystem: departments store courses, students are indexed through a hash table, course prerequisites are mapped using graphs, and resource requests flow through queues. The result is a structured and scalable academic management tool.

# Key Features

• Modular structure with headers, implementations, and data files
• Graph-based course prerequisite manager
• Multi-list structure for department-to-course hierarchy
• Stack-based undo system
• Queue-based request management
• Hash table for fast student lookup
• CRUD operations for academic resources
• Full text-file-based persistence

# Project Structure

/src
main.cpp
graph.h / graph.cpp
department.h / department.cpp
student.h / student.cpp
resource.h / resource.cpp
stack.h / stack.cpp
queue.h / queue.cpp
hashtable.h / hashtable.cpp
multilist.h / multilist.cpp

/data
departments.txt
courses.txt
students.txt
resources.txt

/docs
architecture.puml
system_design.png

README.txt

# System Architecture

The architecture is divided into layers:

Data Layer:
Stores raw information in .txt files.

Core Data Structures Layer:
Custom implementations of arrays, linked lists, multi-lists, stacks, queues, hash tables, and graphs.

Logic Layer:
Modules for departments, resources, students, and prerequisites.

Interaction Layer:
The main.cpp file integrates all modules and controls execution flow.

How the System Works (Human Explanation)

Departments are stored as nodes, and courses under each department are managed through a multi-list structure. The multi-list allows each department to link to its course list dynamically.

Student records use a hash table for quick lookup. When searching for a student, the ID is hashed to an index, allowing near-instant access.

Course prerequisites are represented using a graph. Each course is a node, and directed edges indicate prerequisite requirements. This makes it possible to validate course pathways and detect circular dependencies.

Resource requests (such as notes or books) use a queue structure, ensuring first-come, first-served processing. The undo stack allows rollback of recent operations.

All data is saved into .txt files so that the system can reload previous state on startup.

Data Structures Used

Arrays:
Used for fixed-size indexing and buffering.

Linked Lists:
Used for flexible chains of items such as course lists.

Multi-lists:
Used for hierarchical structures such as Department → Courses.

Stacks:
Used for undo operations and tracking recent actions.

Queues:
Used to process user or resource requests.

Hash Tables:
Used for fast student record lookup.

Graphs:
Used for course prerequisite mapping.

# Real-World Relevance & Innovation

This project models how an actual university manages its academic ecosystem, but with a uniquely foundational approach: every subsystem is built directly on core data structures instead of relying on pre-made libraries or frameworks. Departments and their courses are organized using a multi-list structure that mirrors real catalog hierarchies. Course prerequisites are validated through a full graph implementation, enabling detection of circular dependencies and proper planning of academic pathways—features used in real registration portals.

Student information is stored in a custom-designed hash table that provides near-instant lookup, reflecting how real student information systems handle thousands of records efficiently. Resource requests follow a queue-driven workflow similar to the systems used in libraries and academic help desks. A stack-based undo mechanism introduces a practical feature often missing in student projects, demonstrating how reversible actions are handled in real software. Together, these structures form a tiny but functional academic management backbone, showing how raw data-structure logic can solve genuine institutional challenges without external databases or heavy frameworks.

File Handling

Data is stored in text files:
departments.txt
courses.txt
students.txt
resources.txt

Each module loads its corresponding data at startup and writes back before exiting.
