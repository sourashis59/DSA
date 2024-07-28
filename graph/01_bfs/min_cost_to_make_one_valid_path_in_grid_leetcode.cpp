//* Question link: https://leetcode.com/problems/shortest-bridge/solutions/670485/c-solution-using-0-1-bfs/


class Solution {
public:

  /*
    Pseudo Intuition:
    ------------------------
    Transform into this problem:

    Going from a cell to it's pointed cell has weight = 0,
                    and to other cells have weight = 1 (cost of changing pointer)

    Find the shortest distance from source to dest                    
  */

    vector<vector<int>> grid;
    int m,n;



    //key means the pointer , and the value means the dir change
    unordered_map<int, pair<int,int>> dxy = {
      {1, {0, 1}},
      {2, {0, -1}},
      {3, {1, 0}},
      {4, {-1, 0}}
    };

    
    bool isSafe(int i, int j){
      return i>=0 && j>=0 && i<m && j<n;
    }
    
    int getEdgeWeight(int i, int j, int dir) {
        return grid[i][j] == dir ? 0 : 1;
    }


    class MyTuple {
    public:
        int i, j;
        int dist;
        MyTuple(int i, int j, int dist): i(i), j(j), dist(dist) {}
    };

    int zero_one_bfs() {
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        deque<MyTuple> q;
        q.push_back(MyTuple(0, 0, 0));
        dist[0][0] = 0;
        visited[0][0] = true;

        while (q.size()) {
            MyTuple u = q.front();
            q.pop_front();

            // printf("\nu = (%d, %d), dist=%d", u.i, u.j, u.dist);
            visited[u.i][u.j] = true;
            if (u.i == m - 1 && u.j == n - 1) 
                return u.dist;
            
            for (const auto &p: dxy) {
                int dir_id = p.first;
                int x = u.i + p.second.first;
                int y = u.j + p.second.second;
                int w = getEdgeWeight(u.i, u.j, dir_id);
                MyTuple v(x, y, u.dist + w);
                
                if (!isSafe(x, y)) continue;
                if (visited[x][y]) continue;
                
                if (dist[u.i][u.j] + w < dist[v.i][v.j]) {
                    dist[v.i][v.j] = dist[u.i][u.j] + w;
                    if (w == 0) q.push_front(v);
                    else /*if (w == 1)*/q.push_back(v);
                }
                
            }
        }
        return -1;
    }

    int minCost(vector<vector<int>>& _grid) {
        grid = _grid;
        m = grid.size();
        n = grid[0].size();

        return zero_one_bfs();
    }
};
