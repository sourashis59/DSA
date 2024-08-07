// https://leetcode.com/problems/edit-distance/submissions/1347172456/
class Solution {
public:
    string s, t;
    int m, n;

    vector<vector<int>> memo;

    // mc(i, j) = min cost to convert s[i...end] to t[j...end]
    int mc(int i, int j) {
        if (i == m && j == n) return 0;
        // delete/insert
        if (i == m) return (n - j);
        if (j == n) return (m - i);
        if (memo[i][j] != - 1) return memo[i][j];

        int res = INT_MAX;
        if (s[i] == t[j]) res = min(res, mc(i + 1, j + 1));
        // replace s[i]
        res = min(res, 1 + mc(i + 1, j + 1));
        // delete s[i]
        res = min(res, 1 + mc(i + 1, j));
        // insert t[j] at start of s[i...end]
        res = min(res, 1 + mc(i, j + 1));

        return memo[i][j] = res;   
    }

    int bottomUp() {
        vector<vector<int>> mc(m + 1, vector<int>(n + 1, -1));
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                if (i == m && j == n) {
                    mc[i][j] = 0;
                    continue;
                }
                // delete/insert
                if (i == m) {
                    mc[i][j] = (n - j);
                    continue;
                }
                if (j == n) {
                    mc[i][j] = (m - i);
                    continue;
                }

                int res = INT_MAX;
                if (s[i] == t[j]) res = min(res, mc[i + 1][j + 1]);
                res = min(res, 1 + mc[i + 1][j + 1]);
                res = min(res, 1 + mc[i + 1][j]);
                res = min(res, 1 + mc[i][j + 1]);

                mc[i][j] = res;   
            }
        }
        return mc[0][0];
    }


    int bottomUpSpaceOptimization() {
        // mc -> mc[i]
        // mcPrev -> mc[i + 1]
        vector<int> mc(n + 1, -1);
        vector<int> mcPrev(n + 1, -1);
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                if (i == m && j == n) {
                    mc[j] = 0;
                    continue;
                }
                // delete/insert
                if (i == m) {
                    mc[j] = (n - j);
                    continue;
                }
                if (j == n) {
                    mc[j] = (m - i);
                    continue;
                }

                int res = INT_MAX;
                if (s[i] == t[j]) res = min(res, mcPrev[j + 1]);
                // replace s[i]
                res = min(res, 1 + mcPrev[j + 1]);
                res = min(res, 1 + mcPrev[j]);
                res = min(res, 1 + mc[j + 1]);

                mc[j] = res;   
            }
            // shift pointers
            mcPrev = mc;
        }
        return mc[0];
    }

    int minDistance(string _s, string _t) {
        s = _s, t = _t;
        m = s.size(), n = t.size();

        memo = vector<vector<int>>(m, vector<int>(n, -1));
        return mc(0, 0);
  
        // return bottomUp();
        // return bottomUpSpaceOptimization();
    }
};
