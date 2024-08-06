// https://leetcode.com/problems/palindrome-partitioning-ii/description/
class Solution {
public:
    int n;
    vector<vector<bool>> isPalin;
    vector<int> memo; 

    void initIsPalin(const string &s) {
        int n = s.size();
        isPalin = vector<vector<bool>>(n + 1, vector<bool>(n + 1, false));
        for (int i = n - 1; i >= 0; --i) {
            // j starts from i-1, because j-1 th subproblem is required for current problem
            for (int j = max(0, i - 1); j < n; ++j) {
                // copy pasta
                if (i >= j || i == j) {
                    isPalin[i][j] = true;
                    continue;
                }
                isPalin[i][j] = s[i] == s[j] && isPalin[i + 1][j - 1];   
            }
        }
    }


    int mc(int i) {
        if (i >= n) return 0;
        if (isPalin[i][n-1]) return 0;
        if (memo[i] != -1) return memo[i];

        int res = INT_MAX;
        for (int j = i; j < n; ++j) {
            if (isPalin[i][j]) {
                res = min(res, 1 + mc(j + 1));
            }
        }
        return memo[i] = res;
    }

    int bottomUp(const string &s) {
        vector<int> mc(n + 1);
        for (int i = n; i >= 0; --i) {
            if (i >= n || isPalin[i][n-1]) {
                mc[i] = 0;
                continue; 
            }
            int res = INT_MAX;
            for (int j = i; j < n; ++j) {
                if (isPalin[i][j]) {
                    res = min(res, 1 + mc[j + 1]);
                }
            }
            mc[i] = res;
        }
        return mc[0];
    }




    /*
        Optimize space of isPalin[][].
        Instead of precomputing this, compute ip[] and ipPrev[] while computing mc[].


    
    */
    int bottomUpSpaceOptimized(const string &s) {
        vector<int> mc(n + 1);
        vector<int> ip(n + 1, false); // ip -> isPalin[i]
        vector<int> ipPrev(n + 1, false); // ipPrev -> isPalin[i + 1]

        for (int i = n; i >= 0; --i) {
            // ---------------- first init isPalin(ip and ipPrev) ----------------
            // copy pasta
            for (int j = max(0, i - 1); j < n; ++j) {
                // copy pasta
                if (i >= j || i == j) {
                    ip[j] = true;
                    continue;
                }
                ip[j] = s[i] == s[j] && ipPrev[j - 1];   
            }
            // shift pointers
            ipPrev = ip;
            // ---------------------------------------------------------------------



            // ----------------- then init mc ----------------------
            // replace each isPalin[i] with ip
            if (i >= n || ip[n-1]) {
                mc[i] = 0;
                continue; 
            }
            int res = INT_MAX;
            for (int j = i; j < n; ++j) {
                // find mc
                if (ip[j]) {
                    res = min(res, 1 + mc[j + 1]);
                }
            }
            mc[i] = res;
        }
        return mc[0];
    }

    int minCut(string s) {
        n = s.size();
        // initIsPalin(s);
  
  
        // memo = vector<int>(n, -1);
        // return mc(0);    

        // return bottomUp(s);
        return bottomUpSpaceOptimized(s);
    }
};
