// https://leetcode.com/problems/longest-increasing-subsequence/
class Solution {
public: 

    vector<int> a;
    int n;

    vector<vector<int>> memo;

    // lis(i, prevInd) = length of longest increasing subsequence 
    // from a[i...end] with previously selected index {prevInd}
    // If no element was selected previously, then prevInd = -1
    // PICK, NOT-PICK STRATEGY
    int lis(int i, int prevInd) {
        if (memo[i][prevInd + 1] != -1) return memo[i][prevInd + 1];
        if (i == n) return 0;

        // dont take
        int l1 = lis(i + 1, prevInd);

        // take (if possible)
        int l2 = 0;
        if (prevInd == -1 || a[prevInd] < a[i])
            l2 = 1 + lis(i + 1, i);
        
        return memo[i][prevInd + 1] = max(l1, l2);
    }

    int topDown() {
        memo = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
        return lis(0, -1);
    }


    int bottomUp() {
        vector<vector<int>> l = vector<vector<int>>(n + 2, vector<int>(n + 1));

        for (int i = n; i >= 0; --i) {
            for (int prevInd = -1; prevInd < i; ++prevInd) {
                // copy pasta
                if (i == n) {
                    l[i][prevInd + 1] = 0;
                    continue;
                }

                // dont take
                int l1 = l[i + 1][prevInd + 1];

                // take (if possible)
                int l2 = 0;
                if (prevInd == -1 || a[prevInd] < a[i])
                    l2 = 1 + l[i + 1][i + 1];
                
                l[i][prevInd + 1] = max(l1, l2);
            }
        }

        int res = 0;
        for (int i = 0; i < n; ++i)
            for (int prevInd = -1; prevInd < i; ++prevInd)
                res = max(res, l[i][prevInd + 1]);
        
        return res;
    }

    int bottomUpSpaceOptimized() {
        /*
            Inside loop, (i) depends on (i, prevInd+1), (i+1, prevInd+1), (i+1, i+1)
            So we can only keep i and i+1 th arrays

            l -> l[i]
            lprev -> l[i+1]
        */
        vector<int> l(n + 1);
        vector<int> lprev(n + 1);
        int maxLen = 0;
        for (int i = n; i >= 0; --i) {
            for (int prevInd = -1; prevInd < i; ++prevInd) {
                // copy pasta
                if (i == n) {
                    l[prevInd + 1] = 0;
                    continue;
                }

                // dont take
                int l1 = lprev[prevInd + 1];

                // take (if possible)
                int l2 = 0;
                if (prevInd == -1 || a[prevInd] < a[i])
                    l2 = 1 + lprev[i + 1];
                
                l[prevInd + 1] = max(l1, l2);

                // new change:
                maxLen = max(maxLen, l[prevInd + 1]);
            }
            // shift pointers
            lprev = l;
        }
        return maxLen;
    }

    int lengthOfLIS(vector<int>& _a) {
        a = _a;
        n = a.size();

        return bottomUpSpaceOptimized();
        // return topDown();
    }
};
