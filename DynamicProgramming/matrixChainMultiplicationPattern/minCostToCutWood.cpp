// https://leetcode.com/problems/minimum-cost-to-cut-a-stick/submissions/1349005404/
class Solution {
public:
    vector<int> cuts;
    vector<vector<int>> memo;

    // mc(i) = min cost to cut a[i...end]
    int mc(int i, int j) {
        if (i > j) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        
        int currLen = cuts[j + 1] - cuts[i - 1];
        int res = INT_MAX;
        for (int k = i; k <= j; ++k) {
            res = min(res, currLen + mc(i, k - 1) + mc(k + 1, j));
        }        
        return memo[i][j] = res;
    }


    int bottomUp() {
        vector<vector<int>> mc(cuts.size() + 1, vector<int>(cuts.size() + 1, -1));
        /* 
        in top down: [n = cut.size() here]
        i goes from 1 to j+1 [because inside for loop, k= i to j, and mc(k+1, j) is called]
        j goes from n-2 to (i-1)  [because inside for loop, k = i to j, and mc(i, k-1) is called]
        
        and, min value of i = 1
             min value of j = n - 2 [because we call mc(1, n - 2)]

        So in bottom up, i should go from (n-2+1) to 1
                    and, j should go from (1-1) to (n-2)
        */
        for (int i = cuts.size() - 1; i >= 1; --i) {
            for (int j = 0; j <= cuts.size() - 2; ++j) {
                if (i > j) {
                    mc[i][j] = 0;
                    continue;
                }
                
                int currLen = cuts[j + 1] - cuts[i - 1];
                int res = INT_MAX;
                for (int k = i; k <= j; ++k) {
                    res = min(res, currLen + mc[i][k - 1] + mc[k + 1][j]);
                }        
                mc[i][j] = res;
            }
        }
        return mc[1][cuts.size() - 2];
    }

    int minCost(int n, vector<int>& _cuts) {
        cuts = vector<int>(1, 0);
        cuts.insert(cuts.end(), _cuts.begin(), _cuts.end());
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        // memo = vector<vector<int>>(cuts.size(), vector<int>(cuts.size(), -1));
        // return mc(1, cuts.size() - 2);

        return bottomUp();
    }
};
