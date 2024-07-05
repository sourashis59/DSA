class Solution {
public:

    int longestCommonSubseqLength(const string &s, const string &t) {
        int m = s.size(), n = t.size();
        vector<vector<int>> lcs = vector<vector<int>>(m + 1, vector<int>(n + 1));

        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                if (i == m || j == n) {
                    lcs[i][j] = 0;
                    continue;
                }
                if (s[i] == t[j]) lcs[i][j] = 1 + lcs[i + 1][j + 1];
                else lcs[i][j] = max(lcs[i + 1][j], lcs[i][j + 1]);
            }
        }
        return lcs[0][0];
    }


    int longestPalindromeSubseq(string s) {
        // intuition: lps(s) = lcs(s, reverse(s))
        string revStr = s;
        reverse(revStr.begin(), revStr.end());
        return longestCommonSubseqLength(s, revStr);
    }
};
