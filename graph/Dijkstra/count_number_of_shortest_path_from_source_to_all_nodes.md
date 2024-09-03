// mal: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/

class Solution {
public:

    class Edge {
        int _from, _to;
        long long _weight;
    public:
        Edge(int from, int to, long long weight): _from(from), _to(to), _weight(weight) {}
        int from() const {return _from;}
        int to() const {return _to;}
        long long weight() const {return _weight;}
    };

    class Graph {
        int n;
        vector<vector<Edge>> adj;
    
    public:
        Graph(int n, vector<vector<int>> &roads) {
            this->n = n;
            adj = vector<vector<Edge>>(n);
            for (const auto &e: roads) {
                int u = e[0], v = e[1];
                long long w = e[2];
                adj[u].push_back(Edge(u, v, w));
                adj[v].push_back(Edge(v, u, w)); 
            }
        }

        int node_count() const {
            return n;
        }

        vector<Edge> edges(int u) const {
            return adj[u];
        }
    };



    class comp {
    public:
        bool operator() (Edge &a, Edge &b) {
            if (a.weight() != b.weight()) return a.weight() > b.weight();
            else if (a.to() != b.to()) return a.to() > b.to();
            else return a.from() > b.from();
        }
    };

    int dijkstra_count_shortest_paths(int source, int dest, const Graph &graph) {
        vector<bool> visited(graph.node_count(), false);
        vector<long long> path_count(graph.node_count(), 0);
        vector<long long> dist(graph.node_count(), LONG_LONG_MAX);
        priority_queue<Edge, vector<Edge>, comp> q;

        q.push({-1, source, 0});
        dist[source] = 0;
        path_count[source] = 1;
        while (q.size()) {
            int u = q.top().to();
            q.pop();

            if (visited[u]) continue;
            visited[u] = true;
            if (u == dest) break;

            for (const auto &e: graph.edges(u)) {
                int v = e.to();
                long long w = e.weight();

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    path_count[v] = path_count[u];
                    q.push(Edge(-1, v, dist[v]));
                } else if (dist[u] + w == dist[v]) {
                    path_count[v] = (path_count[v] + path_count[u]) % (int)(1e9 + 7);
                }
            }
        }

        return path_count[dest];
    }




    int countPaths(int n, vector<vector<int>>& roads) {
        return dijkstra_count_shortest_paths(0, n - 1, Graph(n, roads));
    }
};
