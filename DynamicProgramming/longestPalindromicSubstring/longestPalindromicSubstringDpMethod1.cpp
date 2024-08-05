// https://leetcode.com/problems/longest-palindromic-substring/
class Solution {
public:
    string s;
    vector<vector<int>> memo;

    // l(i, j) = length of longest palindromic substring of s[i...j]
    bool isPalin(int i, int j) {
        if (i >= j || i == j) return true;
        if (memo[i][j] != -1) return memo[i][j];
        return memo[i][j] = s[i] == s[j] && isPalin(i + 1, j - 1);   
    }

    string topDown(const string &s) {
        this->s = s;
        int n = s.size();
        memo = vector<vector<int>>(n, vector<int>(n, -1));

        int maxLen = 0;
        int resStart = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (!isPalin(i, j)) continue;
                int currLen = j - i + 1;
                if (currLen > maxLen) {
                    maxLen = currLen;
                    resStart = i;
                }
            }
        } 
        return s.substr(resStart, maxLen);
    }

     /*
        Rule:
        -----------------------
        If subproblem (i,j) depends on (i+1, j-1)
        And recursive function is called: (i=0, j=n-1).

        Then, in bottom up, approach, 
        i should loop from (n-1) to 0
        and j should loop from (i-1) to (n-1).

        Or, for simplicity make: j -> 0 to (n-1)
    
    */
    string bottomUp(const string &s) {
        int n = s.size();
        vector<vector<int>> isPalin = vector<vector<int>>(n + 1, vector<int>(n + 1, false));

        int maxLen = 1;
        int resStart = 0;
        for (int i = n - 1; i >= 0; --i) {
            // j starts from i-1, because j-1 th subproblem is required for current problem
            for (int j = max(0, i - 1); j < n; ++j) {
                // copy pasta
                if (i >= j || i == j) {
                    isPalin[i][j] = true;
                    continue;
                }
                isPalin[i][j] = s[i] == s[j] && isPalin[i + 1][j - 1];   
                
                // extra code
                if (!isPalin[i][j]) continue;
                int currLen = j - i + 1;
                if (currLen > maxLen) {
                    maxLen = currLen;
                    resStart = i;
                }
            }
        }
        return s.substr(resStart, maxLen);    
    }

    string bottomUpSpaceOptimized(const string &s) {
        int n = s.size();
        // ip -> isPalin[i]
        // ipPrev -> isPalin[i + 1]
        vector<int> ip(n + 1);
        vector<int> ipPrev(n + 1);

        int maxLen = 1;
        int resStart = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = max(0, i - 1); j < n; ++j) {
                // copy pasta
                if (i >= j || i == j) {
                    ip[j] = true;
                    continue;
                }
                ip[j] = s[i] == s[j] && ipPrev[j - 1];   

                // extra code
                if (!ip[j]) continue;
                int currLen = j - i + 1;
                if (currLen > maxLen) {
                    maxLen = currLen;
                    resStart = i;
                }
            }
            ipPrev = ip;
        }
        return s.substr(resStart, maxLen);    
    }

    string longestPalindrome(string s) {
        return bottomUpSpaceOptimized(s);
    }
};
