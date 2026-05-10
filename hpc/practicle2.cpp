#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>
#include <vector>

using namespace std;

class Graph {

    int v;
    vector<vector<int>> adj;

public:

    Graph(int v) {
        this->v = v;
        adj.resize(v);
    }

    // Add edge
    void addEdge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Parallel BFS
    void parallelBfs(int start) {

        queue<int> q;
        vector<bool> visited(v, false);

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS Traversal:\n";

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            cout << node << " -> ";

            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbour = adj[node][i];

                if (!visited[neighbour]) {

                    #pragma omp critical
                    {
                        if (!visited[neighbour]) {
                            visited[neighbour] = true;
                            q.push(neighbour);
                        }
                    }
                }
            }
        }

        cout << endl;
    }

    // Parallel DFS
    void parallelDfs(int start) {

        stack<int> st;
        vector<bool> visited(v, false);

        visited[start] = true;
        st.push(start);

        cout << "\nParallel DFS Traversal:\n";

        while (!st.empty()) {

            int node = st.top();
            st.pop();

            cout << node << " -> ";

            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbour = adj[node][i];

                if (!visited[neighbour]) {

                    #pragma omp critical
                    {
                        if (!visited[neighbour]) {
                            visited[neighbour] = true;
                            st.push(neighbour);
                        }
                    }
                }
            }
        }

        cout << endl;
    }
};

int main() {

    int vertices, edges;

    // Input number of vertices
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    // Input number of edges
    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "\nEnter edges (source destination):\n";

    // Taking edges from user
    for (int i = 0; i < edges; i++) {

        int a, b;
        cin >> a >> b;

        g.addEdge(a, b);
    }

    int start;

    // Starting node
    cout << "\nEnter starting vertex: ";
    cin >> start;

    // BFS
    g.parallelBfs(start);

    // DFS
    g.parallelDfs(start);

    return 0;
}