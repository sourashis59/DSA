//https://leetcode.com/problems/burst-balloons/description/
class Solution {
public:
/*    
Pseudo Intuition:
====================================================
Dynamic Programming:
----------------------------------
If you burst k-th ballon in arr[i...j], then for you can't merge the answers of left and right parts,
because they are not independent.

=========
| TRICK | ------> Instead of bursting the k-th balloon, leave the k-th balloon to be burst at last after bursting 
=========         left and right parts. So here the 2 subproblems are independent.

    
m(i, j) = max point by bursting balloons in range arr[i...j]
            given, arr[i-1] and arr[j+1] balloons were not bursted before arr[i...j]

Note: in the given array, we have to add 1 to both end.
*/  

    vector<int> a;
    int n;

    vector<vector<int>> memo;

    int mc(int i, int j) {
        if (i > j) return 0;
        // if (i == j) return a[i - 1] * a[i] * a[j + 1]; 
        if (memo[i][j] != -1) return memo[i][j];

        int res = 0;
        for (int k = i; k <= j; ++k) {
            res = max(res, mc(i, k - 1) + mc(k + 1, j) + a[i - 1] * a[k] * a[j + 1]);
        }
        return memo[i][j] = res;
    }

    int bottomUp() {
        vector<vector<int>> mc(n, vector<int>(n, -1));
        // mc(i, j) -->
        //                           (k goes from i to j)
        //            calls for i ==> i, i+1, i+2, ..., j+1
        //                      j ==> i-1, i, i+1, ..., j
        //            and, min(i) = 1 and max(j) = n-2
        //            So, we need values for i = 1 to (n-2+1)
        //                                   j = (1-0) to (n-2)  
        for (int i = n - 1; i >= 1; --i) {
            for (int j = 0; j <= n - 2; ++j) {
                if (i > j) {
                    mc[i][j] = 0;
                    continue;
                }
                int res = 0;
                for (int k = i; k <= j; ++k) {
                    res = max(res, mc[i][k - 1] + mc[k + 1][j] + a[i - 1] * a[k] * a[j + 1]);
                }
                mc[i][j] = res;
            }
        }
        return mc[1][n - 2];
    }

    int bottomUpEzz() {
        /*
        If you can't think of the range of i and j for base cases (if it's too complicated),
        just initialize all values of of mc[][] with base case value [0 here].
        
        And loop i,j without considering the base cases. 
        i.e., i = 1 to n-2 and j = n-2 to 1
        */
        vector<vector<int>> mc(n, vector<int>(n, 0));
        for (int i = n - 2; i >= 1; --i) {
            for (int j = 1; j <= n - 2; ++j) {
                if (i > j) {
                    mc[i][j] = 0;
                    continue;
                }
                int res = 0;
                for (int k = i; k <= j; ++k) {
                    res = max(res, mc[i][k - 1] + mc[k + 1][j] + a[i - 1] * a[k] * a[j + 1]);
                }
                mc[i][j] = res;
            }
        }
        return mc[1][n - 2];
    }

    int maxCoins(vector<int>& nums) {   
        a = {1};
        a.insert(a.end(), nums.begin(), nums.end());
        a.push_back(1);
        n = a.size();

        // memo = vector<vector<int>>(n, vector<int>(n, -1));
        // return mc(1, n - 2);

        return bottomUp();
        // return bottomUpEzz();
    }
};
