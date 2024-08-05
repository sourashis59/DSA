// https://leetcode.com/problems/maximum-length-of-repeated-subarray/description/

class Solution {
public:

    int m, n;
    vector<int> s, t;

    vector<vector<int>> memo;
    
    // l(i, j) = longest common substring 
    // starting from i-th index of s and
    // j-th index of t 
    int l(int i, int j) {
        if (i == m || j == n) return 0;
        if (memo[i][j] != -1) return memo[i][j];

        int res = 0;
        if (s[i] == t[j]) res = 1 + l(i + 1, j + 1);
        else res = 0;
        return memo[i][j] = res;
    }

    int topDown() {
        memo = vector<vector<int>>(m + 1, vector<int>(n + 1, -1));
        int res = 0;
        for (int i = 0; i < m; ++i) 
            for (int j = 0; j < n; ++j)
                res = max(res, l(i, j));
        
        return res;
    }

    int bottomUp() {
        vector<vector<int>> l = vector<vector<int>>(m + 1, vector<int>(n + 1, -1));
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                // copy paste
                if (i == m || j == n) {
                    l[i][j] = 0;
                    continue;
                }

                int res = 0;
                if (s[i] == t[j]) res = 1 + l[i + 1][j + 1];
                else res = 0;
                l[i][j] = res;
            }
        }

        int res = 0;
        for (int i = 0; i < m; ++i) 
            for (int j = 0; j < n; ++j)
                res = max(res, l[i][j]);
        
        return res;
    }

    int bottomUpSpaceOptimized() {
        // (i,j) is dependent on: (i+1, j+1). ==> we can only keep i and i+1 th array
        // l -> l[i]
        // lprev -> l[i+1]
        vector<int> l(n + 1);
        vector<int> lprev(n + 1);
        int maxLen = 0;
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                // copy paste
                if (i == m || j == n) {
                    l[j] = 0;
                    continue;
                }

                int res = 0;
                if (s[i] == t[j]) res = 1 + lprev[j + 1];
                else res = 0;
                l[j] = res;

                // extra line
                maxLen = max(maxLen, l[j]);
            }
            // shift pointers
            lprev = l;
        }
        return maxLen;
    }


    int findLength(vector<int>& s, vector<int>& t) {
        this->s = s;
        this->t = t;
        m = s.size(), n = t.size();

        return bottomUpSpaceOptimized();
    }
};
