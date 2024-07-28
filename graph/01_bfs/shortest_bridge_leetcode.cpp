//Link: https://leetcode.com/problems/shortest-bridge/


/*
Method3: [0-1 BFS]:

- Pick any 1 node. 
- Do variation 0-1 BFS from it. 
    (Edges between 2 cells of 1 value have 0 weight. The rest(0-0 and 1-0) have a weight of 1.)

After starting 0-1 BFS from any 1 node, when you first encounter 0, set some flag.
After that if you visited 1 node, then that 1 is from different island. (use the flag to detect)
Shortest distance from the source 1 to this 1 is the answer    
*/

vector<vector<int>> dxy = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class MyTuple {
public:
    int i, j;
    int dist;
    MyTuple(int i, int j, int dist): i(i), j(j), dist(dist) {}
};

int zero_one_bfs_helper(int sourcei, int sourcej, vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    dist[sourcei][sourcej] = 0;
    visited[sourcei][sourcej] = false;

    deque<MyTuple> q;
    q.push_back({sourcei, sourcej, 0});
    bool zero_node_visited = false;
    while (q.size()) {
        MyTuple u = q.front();
        q.pop_front();

        printf("\nu=%d, %d,  dist=%d", u.i, u.j, u.dist);
        if (grid[u.i][u.j] == 1 && zero_node_visited) 
            return u.dist - 1;
        
        visited[u.i][u.j] = true;
        if (grid[u.i][u.j] == 0)
            zero_node_visited = true;
        
        for (const auto &dir: dxy) {
            int x = u.i + dir[0];
            int y = u.j + dir[1];
            if (!isSafe(x, y, m, n)) continue;
            if (visited[x][y]) continue;

            int w = (grid[u.i][u.j] != grid[x][y] || grid[u.i][u.j] == 0) ? 1 : 0;
            MyTuple v(x, y, dist[u.i][u.j] + w);

            
            if (dist[u.i][u.j] + w < dist[v.i][v.j]) {
                dist[v.i][v.j] = dist[u.i][u.j] + w;
                if (w == 0) q.push_front(v);
                else /*if (w == 1)*/q.push_back(v);
            }
        }
    }
    return -1;
}

int method3(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) return zero_one_bfs_helper(i, j, grid);
        } 
    }
    return -1;
}
