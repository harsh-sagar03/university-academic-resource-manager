#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// A small, honest graph class meant for handling course prerequisites.
// Nothing fancy, just the tools you actually need for topo sort,
// cycle detection, and semester planning.

class Graph {
public:
    // Create a graph with n courses (0‑indexed).
    Graph(int n);

    // Add a directed edge: prereq → course.
    void addEdge(int prereq, int course);

    // Check if the prereq chain is broken (cycle exists).
    bool hasCycle();

    // Get one valid course‑taking order.
    vector<int> topologicalSort();

    // Group courses semester‑wise (layered topo).
    vector<vector<int>> semesterPlan();

    // Print the graph neatly — nice for debugging.
    void printGraph() const;

private:
    int nodes;
    vector<vector<int>> adj;

    // Helpers for detecting cycles using DFS.
    bool dfsCycle(int node, vector<int> &state);
};

#endif
