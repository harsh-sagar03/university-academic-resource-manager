#include "graph.h"
using namespace std;

// Simple constructor — just make space for everyone.
Graph::Graph(int n) : nodes(n), adj(n) {}

// Add a directed edge prereq → course.
void Graph::addEdge(int prereq, int course) {
    if (prereq >= 0 && prereq < nodes && course >= 0 && course < nodes) {
        adj[prereq].push_back(course);
    } else {
        cout << "Edge out of bounds, ignoring.\n";
    }
}

// DFS helper for cycle detection.
// state: 0 = unvisited, 1 = in-progress, 2 = done.
bool Graph::dfsCycle(int node, vector<int> &state) {
    state[node] = 1; // exploring

    for (int nxt : adj[node]) {
        if (state[nxt] == 1)
            return true; // cycle
        if (state[nxt] == 0 && dfsCycle(nxt, state))
            return true;
    }

    state[node] = 2; // finished
    return false;
}

// Public cycle check.
bool Graph::hasCycle() {
    vector<int> state(nodes, 0);

    for (int i = 0; i < nodes; i++) {
        if (state[i] == 0) {
            if (dfsCycle(i, state))
                return true;
        }
    }
    return false;
}

// Classic Kahn topo sort.
vector<int> Graph::topologicalSort() {
    vector<int> indegree(nodes, 0);

    for (int i = 0; i < nodes; i++)
        for (int x : adj[i])
            indegree[x]++;

    queue<int> q;
    for (int i = 0; i < nodes; i++)
        if (indegree[i] == 0)
            q.push(i);

    vector<int> order;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        order.push_back(cur);

        for (int nxt : adj[cur]) {
            indegree[nxt]--;
            if (indegree[nxt] == 0)
                q.push(nxt);
        }
    }

    if ((int)order.size() != nodes) {
        cout << "Cannot produce topo order — cycle exists.\n";
        return {};
    }

    return order;
}

// Same idea as topo sort, but keep layers separate.
vector<vector<int>> Graph::semesterPlan() {
    vector<int> indegree(nodes, 0);

    for (int i = 0; i < nodes; i++)
        for (int x : adj[i])
            indegree[x]++;

    queue<int> q;
    for (int i = 0; i < nodes; i++)
        if (indegree[i] == 0)
            q.push(i);

    vector<vector<int>> semesters;

    while (!q.empty()) {
        int layerSize = q.size();
        vector<int> currentSem;

        while (layerSize--) {
            int cur = q.front();
            q.pop();
            currentSem.push_back(cur);

            for (int nxt : adj[cur]) {
                indegree[nxt]--;
                if (indegree[nxt] == 0)
                    q.push(nxt);
            }
        }

        semesters.push_back(currentSem);
    }

    int total = 0;
    for (auto &v : semesters) total += v.size();

    if (total != nodes) {
        cout << "Cannot create semester plan — cycle exists.\n";
        return {};
    }

    return semesters;
}

// Handy for debugging.
void Graph::printGraph() const {
    for (int i = 0; i < nodes; i++) {
        cout << i << " -> ";
        for (int x : adj[i])
            cout << x << " ";
        cout << "\n";
    }
}