- Problem: https://www.geeksforgeeks.org/problems/articulation-point-1/1
  
```C

class Solution {
  public:
    vector<vector<int>> adj;
    vector<int> dt; 
    vector<int> low;


    void dfs(int u, int parent, int &curr_time, vector<bool> &visited, 
				    vector<int> &res) {
        visited[u] = true;
        low[u] = dt[u] = curr_time++;
        
        // No of tree edges from u:
        // Needed to check if root is cut vertex
        int tree_edge_count = 0; 
        
        bool u_is_cut_vertex = false;
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
            ++tree_edge_count;
            
            // For non-root vertices (in DFS tree), check if it's cut vertex
            if (parent != -1 && dt[u] <= low[v]) {
                u_is_cut_vertex = true;
            } 
        }
        
        // For root-vertex of DFS spanning tree
        if (parent == -1 && tree_edge_count > 1) 
            u_is_cut_vertex = true;
        
        if (u_is_cut_vertex) res.push_back(u);
    }
    
    vector<int> get_articulation_points(int n, vector<vector<int>>& _adj) {
        adj = _adj;
        dt = vector<int>(n, INT_MAX);
        low = dt;
        vector<bool> visited(n, false);

        int curr_time = 0;
        vector<int> res;
        dfs(0, -1, curr_time, visited, res);
        
        return res;
    }
 
};
```
