class IsTwoColorable {
    vector<bool> marked;
    vector<bool> color;
    int n;

    //* returns true if twoColorable
    bool dfs(int u, const vector<vector<int>> &adj) {
        marked[u] = true;
        for (int v: adj[u]) {
            if (!marked[v]) {
                //* if not marked, assign opposite color
                color[v] = !color[u];
                if (!dfs(v, adj)) 
                    return false;
            }
            //* else if v was marked previously and color is same
            else if (color[u] == color[v])
                return false;
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& adj) {
        n = adj.size();
        marked = vector<bool>(n, false);
        color = vector<bool>(n, false);
        for (int u = 0; u < n; ++u) {
            //* if not marked, then assign 'false' color to u 
            if (!marked[u] && !dfs(u, adj))
                return false;
        }
        return true;
    }
};
