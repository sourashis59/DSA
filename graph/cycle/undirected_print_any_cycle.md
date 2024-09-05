```cpp

int n, m;
vector<vector<int>> adj;


bool dfs(int u, int parent, vector<bool> &visited, vector<int> &parents, vector<int> &res) {
    visited[u] = true;
    for (int v: adj[u]) {
        if (v == parent) continue;
        if (visited[v]) {
            int x = u;
            res.push_back(v);
            while (x != v) {
                res.push_back(x);
                x = parents[x];
            }
            res.push_back(v);
            return true;
        }
        parents[v] = u;
        if (dfs(v, u, visited, parents, res)) return true;
    }
    return false;
}


vector<int> get_cycle() {
    vector<bool> visited(n, false);
    vector<int> parents(n, -1);

    vector<int> res;
    for (int u = 0; u < n; ++u) {
        if (!visited[u] && dfs(u, -1, visited, parents, res)) 
            break;
    }
    return res;
}
```
