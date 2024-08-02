class Solution
{
public:	
	vector<vector<int>> adj;
	
	void dfs_topo_sort(int u, vector<bool> &visited, stack<int> &reversePostorder) {
	    visited[u] = true;
	    for (int v: adj[u]) {
	        if (!visited[v])
	            dfs_topo_sort(v, visited, res);
	    }
	    reversePostorder.push(u);
	}
	 
	vector<int> topoSort(int n, vector<vector<int>>& _adj[])	{
	    adj = _adj;
	    vector<bool> visited(n, false);
	    stack<int> reversePostorder;
	    
	    for (int u = 0; u < n; ++u) {
	        if (!visited[u]) 
	            dfs_topo_sort(u, visited, reversePostorder);
	    }
	    
	    vector<int> res;
	    while (res.size()) {
	        res.push_back(reversePostorder.top());
	        reversePostorder.pop();
	    }
	    return res;
	}
};
