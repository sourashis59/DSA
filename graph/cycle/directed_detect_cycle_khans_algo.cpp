//Khan's algorithm
vector<int> hasCycle(const vector<vector<int>> &adj) {
    int n = adj.size();
    int processedNode = 0;

    // compute indegree
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v: adj[u]) 
            ++indeg[v];

    // start from outer most layer
    queue<int> q;
    for (int u = 0; u < n; ++u) {
        if (indeg[u] == 0) 
            q.push(u);
    }
    
    // one by one remove nodes (with edges) from outer most layer
    while (q.size()) {
        int u = q.front();
        q.pop();
        
        ++processedNode;
        for (int v: adj[u]) {
            --indeg[v];
            if (indeg[v] == 0)
                q.push(v);
        }
    }
    return processedNode == n;
}
