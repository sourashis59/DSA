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
        anc = vector<vector<int>>(MAX_K, vector<int>(n, INT_MIN));
    }
    
    // k-th ancestor of x
    int getKthAncestor(int x, int k) {
        for (int i = 0; i < sizeof(k) * 8; ++i) {
            if (k & (1 << i)) {
                x = getAncK(x, i);
            }
        }
        return x;        
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */