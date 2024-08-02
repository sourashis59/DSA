
/*
Method 2: Double BFS
-----------------------------
Property: center(s) is in the middle of the diameter

From any node, do BFS to find the furthest node (say, x).
This x, is one of the leaf nodes
From x, do BFS to find the furthest node (say, y).
This y, is also one of the leaf nodes.

x ~~> y path is the diameter of the graph.
If this path length is odd, then center = middle node in this path
Else if path length is even, then centers = middle 2 nodes in this path

*/

    // returns {furthest node from source, parent[] array}
    pair<int, vector<int>> bfs(int source, const vector<vector<int>> &adj) {
        int n = adj.size();
        vector<int> parent(n, -2); // use it like visited also: -2 means unvisited
        queue<int> q;
        q.push(source);
        parent[source] = -1;

        int lastNode = -1;
        while (q.size()) {
            int u = q.front();
            q.pop();

            lastNode = u;
            for (int v: adj[u]) {
                // if not visited
                if (parent[v] == -2) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        return {lastNode, parent};
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (const auto &e: edges) {
            int u = e[0], v = e[1];            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        pair<int, vector<int>> bfsRes = bfs(0, adj);
        int x = bfsRes.first;

        bfsRes = bfs(x, adj);
        int y = bfsRes.first;
        vector<int> &parent = bfsRes.second;

        // get path from x to y
        vector<int> path;
        {
            int u = y;
            while (u >= 0) {
                path.push_back(u);
                u = parent[u];
            }
            reverse(path.begin(), path.end());
        }

        // printf("\nx=%d, y=%d", x, y);
        // printf("\nparents: ");
        // for (int p: parent) {
        //     cout << p << ", ";
        // }        

        if (path.size() % 2 == 1) return {path[path.size() / 2]};
        else return {path[path.size() / 2 - 1], path[path.size() / 2]};
    }
