// https://leetcode.com/problems/regular-expression-matching/
class Solution {
public:
    string s, p;
    int m, n;
    
    vector<vector<int>> memo;

    // p will not contain consecutive *s
    // match(i, j) = checks if p[j...end] pattern matches the string s[i...end]
    bool match(int i, int j) {
        // printf("\ni=%d, j=%d", i, j);
        if (i == m && j == n) return true;
        if (j == n) return false;
        if (i == m) {
            // all patterns char should be "something*"
            bool allStar = (n - j) % 2 == 0; //remaining count should be even
            for (int k = j + 1; k < n; k += 2) {
                if (p[k] != '*') {
                    allStar = false;
                    break;
                }
            }
            return allStar;
        }
        if (memo[i][j] != -1) return memo[i][j];
        
        bool res = false;
        if (j + 1 < n && p[j + 1] == '*') {
            // match with empty sequence 
            res = match(i, j + 2);

            // match at least one char
            if (p[j] == '.') res = res || match(i + 1, j);
            else res = res || (s[i] == p[j] && match(i + 1, j)) ;
        } else if (p[j] == '.') {
            res = match(i + 1, j + 1);
        } else if (p[j] != '*') {
            res = (s[i] == p[j] && match(i + 1, j + 1));
        }
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
                    // all patterns char should be "something*"
                    bool allStar = (n - j) % 2 == 0; //remaining count should be even
                    for (int k = j + 1; k < n; k += 2) {
                        if (p[k] != '*') {
                            allStar = false;
                            break;
                        }
                    }
                    match[i][j] = allStar;
                    continue;
                }

                bool res = false;
                if (j + 1 < n && p[j + 1] == '*') {
                    // match with empty sequence 
                    res = match[i][j + 2];

                    // match at least one char
                    if (p[j] == '.') res = res || match[i + 1][j];
                    else res = res || (s[i] == p[j] && match[i + 1][j]) ;
                } else if (p[j] == '.') {
                    res = match[i + 1][j + 1];
                } else if (p[j] != '*') {
                    res = (s[i] == p[j] && match[i + 1][j + 1]);
                }
                match[i][j] = res;
            }
        }
        return match[0][0];
    }


    bool bottomUpSpaceOptimized() {
        // match -> match[i]
        // matchPrev -> match[i + 1]
        vector<int> match(n + 1, -1);
        vector<int> matchPrev(n + 1, -1);
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
                    // all patterns char should be "something*"
                    bool allStar = (n - j) % 2 == 0; //remaining count should be even
                    for (int k = j + 1; k < n; k += 2) {
                        if (p[k] != '*') {
                            allStar = false;
                            break;
                        }
                    }
                    match[j] = allStar;
                    continue;
                }

                bool res = false;
                if (j + 1 < n && p[j + 1] == '*') {
                    // match with empty sequence 
                    res = match[j + 2];

                    // match at least one char
                    if (p[j] == '.') res = res || matchPrev[j];
                    else res = res || (s[i] == p[j] && matchPrev[j]) ;
                } else if (p[j] == '.') {
                    res = matchPrev[j + 1];
                } else if (p[j] != '*') {
                    res = (s[i] == p[j] && matchPrev[j + 1]);
                }
                match[j] = res;
            }
            // shift pointers
            matchPrev = match;
        }
        return match[0];
    }

    string processPattern(const string &p) {
        string res;
        int i = 0;
        while (i < p.size()) {
            res.push_back(p[i]);
            if (p[i] != '*') {
                ++i;
                continue;
            }

            int j = i + 1;
            while (j < p.size() && p[j] == '*')
                ++j;

            i = j; 
        }
        return res;
    }


    /*
    Some corner cases:
    "ab"
    ".*"
    "ab"
    ".*c"
    "abc"
    "a***abc"
    "aab"
    "c*a*b"
    "a"
    "ab*"
    
    */
    bool isMatch(string s, string p) {
        // remove consecutive *s and put only one *, because "**" is equivalent to "*"
        this->p = processPattern(p);
        this->s = s;
        m = s.size();
        n = this->p.size();

        // cout << "\ns=" << s << ", p=" << this->p;

        // memo = vector<vector<int>>(m, vector<int>(n, -1));
        // return match(0, 0);      

        // return bottomUp();
        return bottomUpSpaceOptimized();
    }
};
