- Mal: https://cses.fi/problemset/task/1202/

```cpp

#include<bits/stdc++.h>
using namespace std;


class Edge {
    int _to;
    long long _weight;
public:
    Edge(int to, long long weight): _to(to), _weight(weight) {}
    int to() const {return _to;}
    long long weight() const {return _weight;}
};

class Graph {
    int n;
    vector<vector<Edge>> adj;
public:
    Graph(int n) {
        this->n = n;
        adj = vector<vector<Edge>>(n);
    }

    int V() {
        return n;
    }

    vector<Edge> get_edges(int u) {
        return adj[u];
    }

    void add_edge(int from, int to, long long weight) {
        adj[from].push_back(Edge(to, weight));
    }
};


class comp {
public:
    bool operator() (Edge &a, Edge &b) {
        if (a.weight() != b.weight()) return a.weight() > b.weight();
        else return a.to() > b.to();
    }
};


/*
* Returns:
* 0. Shortest distance from source to dest
* 1. Number of shortest paths
* 2. Min no of edges in shortest path
* 3. Max no of edges in shrotest path
*/

vector<long long> dijkstra_shortest_dist_no_of_shortest_paths_min_and_max_edge_count_in_shortest_path(int source, int dest, Graph &graph) {
    vector<bool> visited(graph.V(), false);
    vector<long long> dist(graph.V(), LONG_LONG_MAX);
    //* path_count[u] = number of shortest paths from source to u till now
    vector<long long> path_count(graph.V(), 0); 
    //* min_edge_count[u] = min number of edges in shortest path from source to u till now
    //* max_edge_count[u] = max number of edges in shortest path from source to u till now
    vector<long long> min_edge_count(graph.V(), 0); 
    vector<long long> max_edge_count(graph.V(), 0); 
    
    priority_queue<Edge, vector<Edge>, comp> q;
    q.push(Edge(source, 0));
    dist[source] = 0;
    path_count[source] = 1;
    min_edge_count[source] = 0;
    max_edge_count[source] = 0;

    while (q.size()) {
        int u = q.top().to();
        q.pop();

        if (visited[u]) continue;
        visited[u] = true;
        if (u == dest) break;

        for (const auto &e: graph.get_edges(u)) {
            int v = e.to();
            long long w = e.weight();

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                path_count[v] = path_count[u];
                min_edge_count[v] = min_edge_count[u] + 1;
                max_edge_count[v] = max_edge_count[u] + 1;
                
                q.push(Edge(v, dist[v]));
            } else if (dist[u] + w == dist[v]) {
                path_count[v] = (path_count[v] + path_count[u]) % (int)(1e9 + 7);
                min_edge_count[v] = min(min_edge_count[v], min_edge_count[u] + 1);
                max_edge_count[v] = max(max_edge_count[v], max_edge_count[u] + 1);
            }
        }
    }

    return {dist[dest], path_count[dest], min_edge_count[dest], max_edge_count[dest]};
}


int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long weight;
        cin >> u >> v >> weight;
        --u, --v;
        graph.add_edge(u, v, weight);
    }

    vector<long long> res = dijkstra_shortest_dist_no_of_shortest_paths_min_and_max_edge_count_in_shortest_path(0, n - 1, graph);
    for (auto ele: res)
        cout << ele << " ";
}
```
