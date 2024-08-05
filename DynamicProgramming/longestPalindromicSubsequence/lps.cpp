// https://leetcode.com/problems/longest-palindromic-subsequence/submissions/1344894592/
class Solution {
public:

    string s;
    int n;

    vector<vector<int>> memo;

    // lps(i, j) = length of LPS from s[i...j]
    int lps(int i, int j) {
        if (i > j) return 0;
        if (i == j) return 1;
        
        if (memo[i][j] != -1) return memo[i][j];
        
        int res = 0;
        if (s[i] == s[j]) res = 2 + lps(i + 1, j - 1);
        else res = max(lps(i, j - 1), lps(i + 1, j));
        return memo[i][j] = res;
    }

    int topDown() {
        memo = vector<vector<int>>(n, vector<int>(n, -1));
        return lps(0, n - 1);
    }


    int bottomUp() {
        vector<vector<int>> lps = vector<vector<int>>(n, vector<int>(n, -1));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = max(0, i - 1); j < n; ++j) {
                // copy paste
                if (i > j) {
                    lps[i][j] = 0;
                    continue;
                }
                if (i == j) {
                    lps[i][j] = 1;
                    continue;
                }
                int res = 0;
                if (s[i] == s[j]) res = 2 + lps[i + 1][j - 1];
                else res = max(lps[i][j - 1], lps[i + 1][j]);
                lps[i][j] = res;
            }
        }
        return lps[0][n - 1];
    }

    int bottomUpSpaceOptimized() {
        /*
            Inside loop, (i, j) depends on: (i+1, j-1), (i, j-1), (i+1, j)
            So, we can keep 2 arrays: i and i+1

            lps -> lps[i]
            lpsPrev -> lps[i+1]
        */
        vector<int> lps(n, -1);
        vector<int> lpsPrev(n, -1);
        // vector<vector<int>> lps = vector<vector<int>>(n, vector<int>(n, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = max(0, i - 1); j < n; ++j) {
                // copy paste
                if (i > j) {
                    lps[j] = 0;
                    continue;
                }
                if (i == j) {
                    lps[j] = 1;
                    continue;
                }
                int res = 0;
                if (s[i] == s[j]) res = 2 + lpsPrev[j - 1];
                else res = max(lps[j - 1], lpsPrev[j]);
                lps[j] = res;
            }
            // shift pointers
            lpsPrev = lps;
        }
        return lps[n - 1];
    }

    int longestPalindromeSubseq(string _s) {
        s = _s;
        n = s.size();    
        
        return bottomUpSpaceOptimized();
        // return bottomUp();
        // return topDown();
    }
};
