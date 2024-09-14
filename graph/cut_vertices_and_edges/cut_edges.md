
- Problem: https://leetcode.com/problems/critical-connections-in-a-network/description/
```c

class Solution {
public:
    vector<vector<int>> adj;
    vector<int> dt; 
    vector<int> low;


    void dfs(int u, int parent, int &curr_time, vector<bool> &visited, 
					    vector<vector<int>> &res) {
        visited[u] = true;
        low[u] = dt[u] = curr_time++;
        bool parent_found_once = false;
        for (int v: adj[u]) {
            if (v == parent && !parent_found_once) {
                parent_found_once = true;
                continue;
            }

            if (visited[v]) {
                if (dt[v] < dt[u]) {
                    // u-->v is a back edge
                    low[u] = min(low[u], dt[v]);
                } 
                continue;
            }

            // u--> v is tree edge
            dfs(v, u, curr_time, visited, res);
            low[u] = min(low[u], low[v]);

            // check if this tree edge is back edge or not 
            if (low[v] > dt[u])
                res.push_back({u, v});
        }
    }

    vector<vector<int>> find_bridges(int n, vector<vector<int>>& _adj) {
        adj = _adj;
        dt = vector<int>(n, INT_MAX);
        low = dt;
        vector<bool> visited(n, false);

        int curr_time = 0;
        vector<vector<int>> res;
        dfs(0, -1, curr_time, visited, res);
        
        return res;
    }
};
```
