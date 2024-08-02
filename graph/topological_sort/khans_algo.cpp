class Solution
{
	public:
    //Function to return list containing vertices in Topological order. 
    vector<int> topoSort(int n, vector<int> adj[])	{
        vector<int> res;
    
        // compute indegree
        vector<int> indeg(n, 0);
        for (int u = 0; u < n; ++u)
            for (int v: adj[u]) 
                ++indeg[v];
    
        // start from outer most layer
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (indeg[u] == 0) 
                q.push(u);
        }
        
        // one by one remove nodes (with edges) from outer most layer
        while (q.size()) {
            int u = q.front();
            q.pop();
            
            res.push_back(u);
            for (int v: adj[u]) {
                --indeg[v];
                if (indeg[v] == 0)
                    q.push(v);
            }
        }
        
        // cycle 
        if (res.size() != n)
            return {};
        
        return res;
    }





/*
If you want the layer number of all nodes:

    vector<int> topoSort(int n, vector<int> adj[])	{
        vector<int> res;
    
        // compute indegree
        vector<int> indeg(n, 0);
        for (int u = 0; u < n; ++u)
            for (int v: adj[u]) 
                ++indeg[v];
    
        // start from outer most layer
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (indeg[u] == 0) 
                q.push(u);
        }

        vector<int> level(n);
        int currentLevel = 0;
        // one by one remove nodes (with edges) from outer most layer
        while (q.size()) {
            // processing all nodes of the i-th layer
            int qSize = q.size();
            while (qSize--) {
                int u = q.front();
                q.pop();

                level[u] = currLevel;
                res.push_back(u);
                for (int v: adj[u]) {
                    --indeg[v];
                    if (indeg[v] == 0)
                        q.push(v);
                }   
            }

            //increase the level
            ++currLevel;
        }
        
        // cycle 
        if (res.size() != n)
            return {};
        
        return res;
    }


*/




};
