
class Solution {
    vector<bool> visited;
    
    bool dfsHasCycle(int u, int parent, vector<int> adj[]) {
        visited[u] = true;
        for (int v: adj[u]) {
            if (v == parent) continue;
            if (visited[v]) return true;
            if (dfsHasCycle(v, u, adj)) return true;
        }
        return false;
    }
    
  public:
    bool isCycle(int n, vector<int> adj[]) {
        visited = vector<bool>(n, false);
        for (int u = 0; u < n; ++u) {
            if (!visited[u] && dfsHasCycle(u, -1, adj))
                return true;
        }
        return false;
    }
};
