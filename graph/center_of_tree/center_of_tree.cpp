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



// Alternate:
// vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
//         vector<vector<int>> adj(n);
//         vector<int> deg(n, 0);
        
//         // // if you need the layers also
//         // vector<int> allLevels;

//         for (const auto &e: edges) {
//             int u = e[0], v = e[1];
            
//             adj[u].push_back(v);
//             adj[v].push_back(u);

//             ++deg[u];
//             ++deg[v];
//         }

//         // enqueue the outer most layer
//         queue<int> q;
//         for (int u = 0; u < n; ++u) {
//             //degree == 1
//             if (deg[u] <= 1) {
//                 q.push(u);
//             }
//         }

//         int remainingNodes = n;
//         while (remainingNodes > 2) {
//             // process the current outermost level
//             int levelSize = q.size();
//             remainingNodes -= levelSize;
//             // vector<int> currLevel;

//             for (int i = 0; i < levelSize; ++i) {    
//                 int u = q.front();
//                 q.pop();

//                 // remove u from the graph along with the edges
//                 // At the time of popping from queue, u can have only one edge
                
//                 // make outdegree[u] = 0
//                 deg[u] = 0;
//                 // currLevel.push_back(u);

//                 for (int v: adj[u]) {
//                     // remove the edge u->v [indeg[v] -= 1]
//                     --deg[v];
//                     if (deg[v] == 1) {
//                         q.push(v);
//                     }
//                 }
//             }

//             // keep the current level
//             // allLevels.push_back(currLevel);
//         }

//         vector<int> res;
//         while (q.size()) {
//             res.push_back(q.front());
//             q.pop();
//         }
//         return res;
//     }
};
