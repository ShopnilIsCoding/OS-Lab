#include<bits/stdc++.h>
using namespace std;

unordered_map<char, vector<char>> adjList;
unordered_map<char, bool> visited;
unordered_map<char, bool> onStack;

bool hasCycle(char node, vector<char>& cycle) {
    visited[node] = true;
    onStack[node] = true;
    cycle.push_back(node);

    for (char neighbor : adjList[node]) {
        if (!visited[neighbor]) {
            if (hasCycle(neighbor, cycle))
                return true;
        } else if (onStack[neighbor]) {
            cycle.push_back(neighbor); 
            return true;
        }
    }

    onStack[node] = false;
    cycle.pop_back();
    return false;
}

void addEdge(char source, char destination) {
    adjList[source].push_back(destination);
    if (visited.find(source) == visited.end())
        visited[source] = false;
    if (visited.find(destination) == visited.end())
        visited[destination] = false;
    onStack[source] = false;
    onStack[destination] = false;
}

bool detectDeadlock() {
    for (auto& node : adjList) {
        vector<char> cycle;
        if (!visited[node.first]) {
            if (hasCycle(node.first, cycle)) {
                cout << "Deadlock: Yes\n";
                return true;
            }
        }
    }
    cout << "Deadlock: No\n";
    return false;
}

int main() {
    int numNodes, numEdges;
    cout << "Number of Nodes: ";
    cin >> numNodes;
    cout << "Number of Edges: ";
    cin >> numEdges;

    cout << "Edges:" << endl;
    for (int i = 0; i < numEdges; i++) {
        char source, destination;
        cin >> source >> destination;
        addEdge(source, destination);
    }

    detectDeadlock();

    return 0;
}
