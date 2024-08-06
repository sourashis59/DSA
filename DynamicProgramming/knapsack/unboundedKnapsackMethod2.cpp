// THIS METHOD IS USEFUL FOR COUNTING COMBINATIONS
// https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
class Solution{
    int n;
    int *val, *wt;
    
    vector<vector<int>> memo;
        
    // mv(i, c) = max value we can get using val[i...end]
    //            with total weight <= c
    int mv(int i, int c) {
        if (i == n) return 0;
        if (memo[i][c] != -1) return memo[i][c];
        
        // dont take any val[i]
        int m1 = mv(i + 1, c);
        // take one val[i], if possible
        int m2 = 0;
        if (wt[i] <= c) m2 = val[i] + mv(i, c - wt[i]);
        
        return memo[i][c] = max(m1, m2);
    }
    
    int bottomUp(int targetW) {
        vector<vector<int>> mv(n + 1, vector<int>(targetW + 1, -1));
        for (int i = n; i >= 0; --i) {
            for (int c = 0; c <= targetW; ++c) {
                // copy pasta
                if (i == n) {
                    mv[i][c] = 0;
                    continue;
                }

                // dont take any val[i]
                int m1 = mv[i + 1][c];
                // take one val[i], if possible
                int m2 = 0;
                if (wt[i] <= c) m2 = val[i] + mv[i][c - wt[i]];
                
                mv[i][c] = max(m1, m2);
            }
        }
        return mv[0][targetW];
    }
    
    int bottomUpSpaceOptimized(int targetW) {
        // mv -> mv[i]
        // mvPrev -> mv[i + 1]
        vector<int> mv(targetW + 1, -1);
        vector<int> mvPrev(targetW + 1, -1);
        for (int i = n; i >= 0; --i) {
            for (int c = 0; c <= targetW; ++c) {
                // copy pasta
                if (i == n) {
                    mv[c] = 0;
                    continue;
                }

                // dont take any val[i]
                int m1 = mvPrev[c];
                // take one val[i], if possible
                int m2 = 0;
                if (wt[i] <= c) m2 = val[i] + mv[c - wt[i]];
                
                mv[c] = max(m1, m2);
            }
            // shift pointers
            mvPrev = mv;
        }
        return mv[targetW];
    }
    
public:
    int knapSack(int _n, int _w, int val[], int wt[]) {
        n = _n;
        this->val = val;
        this->wt = wt;
            
        return bottomUpSpaceOptimized(_w);
        return bottomUp(_w);
        
        memo = vector<vector<int>>(n, vector<int>(_w + 1, -1));
        return mv(0, _w);    
    }
};
