class Solution {
public: 

    vector<int> a;
    int n;

    vector<int> memo;

    // lis(i) = length of longest increasing subsequence 
    // starting from i-th index of a[]
    int lis(int i) {
        if (memo[i] != -1) return memo[i];
        if (i == n - 1) return 1;
        int res = 0;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] > a[i]) 
                res = max(res, lis(j));
        }
        return memo[i] = res + 1;
    }

    int topDown() {
        memo = vector<int>(n + 1, -1);
        int res = 0;
        for (int i = 0; i < n; ++i)
            res = max(res, lis(i));
        
        return res;
    }

    int bottomUp() {
        vector<int> l = vector<int>(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            // copy pasta
            if (i == n - 1) {
                l[i] = 1;
                continue;
            }
            int res = 0;
            for (int j = i + 1; j < n; ++j) {
                if (a[j] > a[i]) 
                    res = max(res, l[j]);
            }
            l[i] = res + 1;
        }

        int res = 0;
        for (int i = 0; i < n; ++i)
            res = max(res, l[i]);
        
        return res;
    }

    int lengthOfLIS(vector<int>& _a) {
        a = _a;
        n = a.size();

        return bottomUp();
        // return topDown();
    }
};
