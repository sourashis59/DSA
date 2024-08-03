// returns true if cycle found
bool dfs(int u, vector<bool> &dfsStarted, vector<bool> &dfsFinished,
            vector<int> &res,
            const vector<vector<int>> &adj) {
    dfsStarted[u] = true;
    for (int v: adj[u]) {
        if (dfsStarted[v] && !dfsFinished[v]) return true;
        else if (!dfsStarted[v] && dfs(v, dfsStarted, dfsFinished, res, adj)) return true; 
    }
    dfsFinished[u] = true;
    res.push_back(u);
    return false;
}

vector<int> getTopoOrder(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> dfsStarted(n, false);
    vector<bool> dfsFinished(n, false);
    vector<int> res;
    for (int u = 0; u < n; ++u) {
        // if cycle found, dfs(...) return true
        if (!dfsStarted[u] && dfs(u, dfsStarted, dfsFinished, res, adj))
            return {};
            
    }
    reverse(res.begin(), res.end());
    return res;
}
