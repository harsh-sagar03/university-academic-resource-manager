#include "graph.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

static unordered_map<int,int> origToIdx;
static vector<int> idxToOrig;

Graph globalGraph(0);

using namespace std;

// Simple constructor — just make space for everyone.
Graph::Graph(int n) : nodes(0), adj(0) {
    origToIdx.clear();
    idxToOrig.clear();
}

// Add a directed edge prereq → course.
void Graph::addEdge(int prereq, int course) {
    auto getIdx = [&](int x){
        if(origToIdx.count(x)) return origToIdx[x];
        int newIdx = idxToOrig.size();
        origToIdx[x] = newIdx;
        idxToOrig.push_back(x);
        adj.resize(newIdx+1);
        nodes = newIdx+1;
        return newIdx;
    };

    int u = getIdx(prereq);
    int v = getIdx(course);
    adj[u].push_back(v);
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

    for(int x : order){
        cout << idxToOrig[x] << " ";
    }
    cout << endl;

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

    for(int i = 0; i < semesters.size(); i++){
        cout << "Semester " << (i+1) << ": ";
        for(int x : semesters[i]){
            cout << idxToOrig[x] << " ";
        }
        cout << "\n";
    }

    return semesters;
}

// Handy for debugging.
void Graph::printGraph() const {
    for (int i = 0; i < nodes; i++) {
        cout << idxToOrig[i] << " -> ";
        for (int x : adj[i])
            cout << idxToOrig[x] << " ";
        cout << "\n";
    }
}



/* ===================== FILE HANDLING (CLASS METHODS) ===================== */

void Graph::loadFromFile() {
    ifstream fin("graph.txt");
    if (!fin.is_open()) return;

    origToIdx.clear();
    idxToOrig.clear();
    nodes = 0;
    adj.clear();

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        size_t pos = line.find("->");
        if (pos == string::npos) continue;

        int u = stoi(line.substr(0, pos));
        int v = stoi(line.substr(pos + 2));

        addEdge(u, v);
    }

    fin.close();
}

void Graph::saveToFile() const {
    ofstream fout("graph.txt");
    if (!fout.is_open()) return;
    for (int u = 0; u < nodes; u++) {
        for (int v : adj[u])
            fout << idxToOrig[u] << "->" << idxToOrig[v] << "\n";
    }
    fout.close();
}