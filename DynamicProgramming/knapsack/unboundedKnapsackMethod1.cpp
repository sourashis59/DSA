// THIS METHOD IS USED FOR GETTING PERMUTATIONS
// https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
class Solution{
    int n;
    int *val, *wt;
    
    vector<int> memo;
    
    
    // mv(w) = max val we can get from using val[0...end] 
    //          with total weight <= w
    int mv(int c) {
        if (memo[c] != -1) return memo[c];
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (wt[i] <= c) {
                res = max(res, val[i] + mv(c - wt[i]));
            }
        }
        return memo[c] = res;
    }
    
    
    int bottomUp(int targetW) {
        vector<int> mv(targetW + 1, -1);
        for (int c = 0; c <= targetW; ++c) {
            int res = 0;
            for (int i = 0; i < n; ++i) {
                if (wt[i] <= c) {
                    res = max(res, val[i] + mv[c - wt[i]]);
                }
            }
            mv[c] = res;
        }
        return mv[targetW];
    }
    
    
public:
    int knapSack(int _n, int _w, int val[], int wt[]) {
        n = _n;
        this->val = val;
        this->wt = wt;
        
        return bottomUp(_w);
        
        memo = vector<int>(_w + 1, -1);
        return mv(_w);    
    }
};
