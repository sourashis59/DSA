- Question Link: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/

```cpp
class LCAFinder {
    int root;
    const vector<vector<int>> &adj;
    int n;
    // depth[x] = depth of node x [depth of root is 0]
    vector<int> depth;
    // parent[x] = parent of x 
    vector<int> parent;
    // anc[k][x] = 2^k-th ancestor of x
    // if 2^k is more than depth[x] then value is -1
    int MAX_POW; // 2 ^ MAX_POW = max{depth[x]}
    vector<vector<int>> anc;


    void initDepthAndParent(int root, int curr_parent, int curr_depth) {
        depth[root] = curr_depth;
        parent[root] = curr_parent;
        for (int child: adj[root]) {
            if (child != curr_parent) initDepthAndParent(child, root, curr_depth + 1);
        }
    }

public:
    LCAFinder(int root, const vector<vector<int>> &adj): root(root), adj(adj) {
        n = adj.size();
        depth = vector<int>(n, 0);
        parent = vector<int>(n, -1);
        // init depth and parent
        initDepthAndParent(root, -1, 0);
        
        // init anc
        int max_depth = *max_element(depth.begin(), depth.end());
        MAX_POW = ceil(log2(max_depth));
        anc = vector<vector<int>>(MAX_POW + 1, vector<int>(n, -1));
        for (int k = 0; k <= MAX_POW; ++k) {
            for (int x = 0; x < n; ++x) {
                int res = -1;
                if (k == 0) res = parent[x];
                else if (anc[k - 1][x] != -1) res = anc[k - 1][anc[k - 1][x]];

                anc[k][x] = res;
            }
        }
    }

    // k-th ancestor of x
    // returns -1 if does not exist
    int getKthAnc(int x, int k) {
        if (k > depth[x]) return -1;
        for (int i = 0; i <= MAX_POW; ++i) {
            if (k & (1 << i)) x = anc[i][x];
        }
        return x;
    }   

    // Time complexity = O(logH * logH)
    // There is a variation with time = O(logH). Please check later
    int findLCA(int x, int y) {
        if (depth[x] < depth[y]) swap(x, y);
        // x is at equal or more depth than y
        x = getKthAnc(x, depth[x] - depth[y]);
        // now x and y are at same depth

        // use binary search to find the LCA
        int low = 0, high = depth[x]; // depth range
        int res = x; // potential LCA
        while (low <= high) {
            int mid_depth = low + (high - low) / 2;
            int depth_diff = depth[x] - mid_depth;
            int x_mid = getKthAnc(x, depth_diff), y_mid = getKthAnc(y, depth_diff);
            if (x_mid == y_mid) {
                res = x_mid;    
                low = mid_depth + 1;
            } else {
                high = mid_depth - 1;
            }
        }
        return res;
    }

    int getDist(int x, int y) {
        int lca = findLCA(x, y);
        return depth[x] + depth[y] - 2 * depth[lca];
    }
};

```
