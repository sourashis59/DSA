class Edge {
public:
    int u, v;
    int w;

    Edge(int u, int v, int w): u(u), v(v), w(w) {}
};

class comp {
public:
    bool operator() (const Edge &a, const Edge &b) const {
        if (a.w != b.w) return a.w > b.w;
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    }
};

class MST {
public:
    /*
      Note:
      ----------------
      Priority queue is more efficient than sorting here.
      Because building the priority queue (using heapify algorithm) takes O(E) time.
      Then we remove smallest element from priority_queue one by one [O(logE) time for each pop].
      So worst case time is still O(E * logE)
      But in practical cases, we dont need to pop all edges, because before popping all edges
      usually, MST is formed [i.e., res.size() becomes n-1] 
      
      But in sorting, we have to sort all edges in O(E * logE) always. 
    */
    // returns MST edges
    vector<Edge> getKruskal(int n, vector<Edge> edges) {
        vector<Edge> res; 
        // build heap in linear time 
        priority_queue<Edge, vector<Edge>, comp> q(edges.begin(), edges.end());
        
        DisjointSet ds(n);
        while (q.size() && res.size() < n - 1) {
            Edge e = q.top();
            q.pop();
            if (!ds.connected(e.u, e.v)) {
                ds.doUnion(e.u, e.v);
                res.push_back(e);
            }
        }
        return res;
    }
};
