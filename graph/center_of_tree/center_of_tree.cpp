class Solution {
public:
/*
Pseudo Algorithm:
----------------------------------------------------------------
We will start with the outer most layer (nodes with degree = 1)
Remove those nodes

Again find the outer most layer in the remaining tree
Remove those nodes

....
....
....

If the number of nodes in the outermost layer at some point is 1 ---> then that node is the center
Else if number of nodes in outermost layer is 2 and no. of remaining nodes is also 2 ---> then those 2 are the centers
*/
    vector<int> findCenters(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> adj(n);
        for (const auto &e: edges) {
            int u = e[0], v = e[1];
            adj[u].insert(v);
            adj[v].insert(u);
        }

        queue<int> q;
        for (int u = 0; u < n; ++u) {
            //degree == 1
            if (adj[u].size() <= 1)
                q.push(u);
        }
        int remNodes = n; //remaining nodes
        while (remNodes > 2) {
            int layerSize = q.size();
            remNodes -= layerSize;
            for (int i = 0; i < layerSize; ++i) {    
                int u = q.front();
                q.pop();

                //remove u
                //v is the only connected node to u now
                int v = *adj[u].begin();
                adj[v].erase(u);
                adj[u].erase(v);

                if (adj[v].size() == 1) 
                    q.push(v);
            }
        }

        vector<int> res;
        while (q.size()) {
            res.push_back(q.front());
            q.pop();
        }
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
