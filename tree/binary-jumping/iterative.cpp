class TreeAncestor {
private:
    int root = 0;
    vector<int> p;
    //anc[k][x] = 2^k th ancestor of node x
    vector<vector<int>> anc;
    //max value of k for anc[]
    int MAX_K; 
    
    //2^k th ancestor of x
    int getAncK(int x, int k) {
        if (k == 0) return p[x];
        if (x == root || x == -1) return -1;
        if (anc[k][x] != INT_MIN) return anc[k][x];
        return anc[k][x] = getAncK(getAncK(x, k - 1), k - 1);
    }

public:
    TreeAncestor(int n, vector<int>& parent) {
        p = parent;
        MAX_K = log2(n) + 1;
        anc = vector<vector<int>>(MAX_K, vector<int>(n, -1));

        //init
        for (int u = 0; u < n; ++u) anc[0][u] = parent[u];
        for (int k = 1; k < MAX_K; ++k) {
            for (int u = 0; u < n; ++u) {
                //if not out of bound
                if (anc[k - 1][u] != -1) 
                    anc[k][u] = anc[k - 1][anc[k - 1][u]];
            }
        }
    }
    
    // k-th ancestor of x
    int getKthAncestor(int x, int k) {
        for (int i = 0; i < sizeof(k) * 8; ++i) {
            if (k & (1 << i)) {
                x = anc[i][x];
                if (x == -1) break;
            }
        }
        return x;        
    }
};