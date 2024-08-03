// returns true if cycle found
bool dfs(int u, vector<bool> &dfsStarted, vector<bool> &dfsFinished,
            const vector<vector<int>> &adj) {
    dfsStarted[u] = true;
    for (int v: adj[u]) {
        if (dfsStarted[v] && !dfsFinished[v]) return true;
        else if (!dfsStarted[v] && dfs(v, dfsStarted, dfsFinished, adj)) return true; 
    }
    dfsFinished[u] = true;
    return false;
}

bool hasCycle(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> dfsStarted(n, false);
    vector<bool> dfsFinished(n, false);

    for (int u = 0; u < n; ++u) {
        if (!dfsStarted[u] && dfs(u, dfsStarted, dfsFinished, adj))
            return true;
    }
    return false;
}
