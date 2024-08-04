class Edge {
public:
    int u, v;
    int w;

    Edge(int u, int v, int w): u(u), v(v), w(w) {}
};

struct MyPair {
    int node;
    long long dist;
};

class Prim { 
    class comp {
    public:
        bool operator()(const MyPair& a, const MyPair& b) const {
            if (a.dist != b.dist) return a.dist > b.dist;
            else return a.node < b.node;
        }
    };

public:
    // returns Edges of MST
    vector<Edge> getPrim(vector<vector<MyPair>> &adj) {
        int n = adj.size();
        int s = 0;
        vector<long long> d(n, LONG_LONG_MAX);
        vector<bool> marked(n, false);
        vector<int> parent(n, -1);

        priority_queue<MyPair, vector<MyPair>, comp> q;
        q.push({s, d[s]});
        d[s] = 0;
        int markedCount = 0;
        while (!q.empty() && markedCount < n) {
            MyPair u = q.top();
            q.pop();

            //* in Dijkstra, this optimization is not necessary for correctness.
            //* But in Prim, this is needed for CORRECTNESS
            if (marked[u.node])
                continue;
            
            ++markedCount;
            marked[u.node] = true;
            for (const auto& ele: adj[u.node]) {
                int v = ele.node;
                int w = ele.dist;
                
                //* in Dijkstra, this checking is not needed
                //* But in Prim, it is needed for correctness
                if (marked[v])
                    continue;

                // relax
                // for Dijkstra: newDist = d[u] + w
                long long newDist = w;     
                if (newDist < d[v]) {
                    d[v] = newDist;
                    parent[v] = u.node;
                    q.push({ v, d[v] });
                }
            }
        }

        vector<Edge> res;
        for (int v = 0; v < n; ++v) {
            if (parent[v] == -1) 
                continue;
            int u = parent[v];
            int w = d[v];
            res.push_back(Edge(u, v, w));
        }

        return res;
    }
};
