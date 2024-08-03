class Solution {
    
public:

    vector<bool> dfsStarted;
    vector<bool> dfsFinished;
    vector<int> parent;
    vector<int> oneCycle;
    vector<vector<int>> adj;

    // returns true if cycle found
    bool dfs(int u) {
        dfsStarted[u] = true;
        for (int v: adj[u]) {
            if (dfsStarted[v] && !dfsFinished[v]) {
                // cycle found
                // print cycle
                for (int x = u; x != v; x = parent[x]) 
                    oneCycle.push_back(x);
                    
                oneCycle.push_back(v);
                return true;
            } else if (!dfsStarted[v]) {
                parent[v] = u;
                if (dfs(v)) return true;
            }
        }
        dfsFinished[u] = true;
        return false;
    }

    bool hasCycle(const vector<vector<int>> &adj) {
        int n = adj.size();
        dfsStarted= vector<bool>(n, false);
        dfsFinished = vector<bool>(n, false);
        parent = vector<int>(n, -1);
        oneCycle = vector<int>();
        this->adj = adj;
        
        bool res = false;
        for (int u = 0; u < n; ++u) {
            if (!dfsStarted[u] && dfs(u))
                res = true;
        }

        printf("\nCycle: ");
        for (int x: oneCycle) 
            cout << x << ", ";
            
        return res;
    }
};
