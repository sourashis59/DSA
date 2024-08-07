// https://leetcode.com/problems/wildcard-matching/description/
class Solution {
public:
    string s, p;
    int m, n;
    
    vector<vector<int>> memo;

    // match(i, j) = checks if p[j...end] pattern matches the string s[i...end]
    bool match(int i, int j) {
        if (memo[i][j] != -1) return memo[i][j];

        // printf("\ni=%d, j=%d", i, j);
        if (i == m && j == n) return memo[i][j] = true;
        if (j == n) return memo[i][j] = false;
        if (i == m) {
            for (int k = j; k < n; ++k) if (p[k] != '*') return memo[i][j] = false;
            return memo[i][j] = true;
        }
        
        bool res = false;
        if (p[j] == '?') 
            res = match(i + 1, j + 1);
        else if (p[j] == '*') {
            // match empty sequence 
            // || use the * to match atleast s[i] (and may be next characters too)
            res = match(i, j + 1) || match(i + 1, j);
        }
        else 
            res = s[i] == p[j] && match(i + 1, j + 1);
        
        return memo[i][j] = res;
    }

    bool bottomUp() {
        vector<vector<int>> match(m + 1, vector<int>(n + 1, -1));
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                if (i == m && j == n) {
                    match[i][j] = true;
                    continue;
                }
                if (j == n) {
                    match[i][j] = false;
                    continue;
                }
                if (i == m) {
                    bool allStar = true;
                    for (int k = j; k < n; ++k) if (p[k] != '*') {
                        allStar = false;
                        break;
                    }
                    match[i][j] = allStar;
                    continue;
                }
                
                bool res = false;
                if (p[j] == '?') 
                    res = match[i + 1][j + 1];
                else if (p[j] == '*') 
                    res = match[i][j + 1] || match[i + 1][j];
                else 
                    res = s[i] == p[j] && match[i + 1][j + 1];
                
                match[i][j] = res;
            }
        }
        return match[0][0];
    }

    bool bottomUpSpaceOptimized() {
        // match -> match[i]
        // matchPrev -> match[i + 1]
        vector<int> match(n + 1, false);
        vector<int> matchPrev(n + 1, false);
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                if (i == m && j == n) {
                    match[j] = true;
                    continue;
                }
                if (j == n) {
                    match[j] = false;
                    continue;
                }
                if (i == m) {
                    bool allStar = true;
                    for (int k = j; k < n; ++k) if (p[k] != '*') {
                        allStar = false;
                        break;
                    }
                    match[j] = allStar;
                    continue;
                }
                
                bool res = false;
                if (p[j] == '?') 
                    res = matchPrev[j + 1];
                else if (p[j] == '*') 
                    res = match[j + 1] || matchPrev[j];
                else 
                    res = s[i] == p[j] && matchPrev[j + 1];
                
                match[j] = res;
            }
            matchPrev = match;
        }
        return match[0];
    }

    bool isMatch(string s, string p) {
        this->s = s;
        this->p = p;
        m = s.size();
        n = p.size();

        // memo = vector<vector<int>>(m + 1, vector<int>(n + 1, -1));
        // return match(0, 0);

        // return bottomUp();
        return bottomUpSpaceOptimized();
    }
};
