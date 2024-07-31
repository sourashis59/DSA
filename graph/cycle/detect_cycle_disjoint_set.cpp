    bool isCycle(int n, vector<int> adj[]) {
        //* detect parallel edges and self loops
        unordered_set<int> adjNodes;
        for (int u = 0; u < n; ++u) {
            adjNodes.clear();
            for (int v: adj[u]) {
                //* parallel edge detected
                if (adjNodes.count(v)) return true;
                //* self loop
                if (u == v) return true;
                
                adjNodes.insert(v);
            }
        }
        
        DisjointSet ds(n);
        for (int u = 0; u < n; ++u) {
            for (int v: adj[u]) {
                //* check only unique edges
                //* Because, in undirected graph, we have both u->v and v->u
                
                //* if u > v, then this edge was already processed 
                //* while procesing v
                if (u > v) 
                    continue;
                
                if (ds.connected(u, v)) 
                    return true;
                
                ds.doUnion(u, v);
            }
        }
        return false;
    }
