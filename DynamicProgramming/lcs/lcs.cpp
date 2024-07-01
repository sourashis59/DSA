class Solution {
public:
    string s, t;
    int m, n;
    
    vector<vector<int>> memo;


    // l(i, j) = length of lcs of s[i...end] and t[i...end]
    int l(int i, int j) {
        if (i == m || j == n) return 0;
        if (memo[i][j] != -1) return memo[i][j];

        int res = 0;
        if (s[i] == t[j]) res = 1 + l(i + 1, j + 1);
        else res = max(l(i, j + 1), l(i + 1, j));
        return memo[i][j] = res;
    }
    

    int bottomUp() {
        vector<vector<int>> l(m + 1, vector<int>(n + 1, 0));
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                if (i == m || j == n) {
                    l[i][j] = 0;
                    continue;
                }

                int res = 0;
                if (s[i] == t[j]) res = 1 + l[i + 1][j + 1];
                else res = max(l[i][j + 1], l[i + 1][j]);
                l[i][j] = res;
            }
        }
        return l[0][0];
    }

    int longestCommonSubsequence(string _s, string _t) {
        s = _s;
        t = _t;
        m = s.size();
        n = t.size();

        return bottomUp();

        // memo = vector<vector<int>>(m, vector<int>(n, -1));
        // return l(0, 0);
    }
};
