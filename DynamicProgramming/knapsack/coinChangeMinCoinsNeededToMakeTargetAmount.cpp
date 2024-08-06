// EASY Questions, no need to revise :=
// https://leetcode.com/problems/coin-change/description/
class Solution {
public:
    vector<int> coins;
    int n;

    vector<vector<int>> memo;

    int mc(int i, int target) {
        if (target == 0) return 0;
        if (i == n) return -1; // impossible
        if (memo[i][target] != INT_MIN) return memo[i][target];

        int res = INT_MAX;
        int m1 = mc(i + 1, target);
        if (m1 != -1) res = min(res, m1);
        
        int m2 = -1;
        if (coins[i] <= target) m2 = mc(i, target - coins[i]);
        if (m2 != -1) res = min(res, 1 + m2);

        if (res == INT_MAX) res = -1;
        return memo[i][target] = res;
    }

    int bottomUp(int targetAmount) {
        vector<vector<int>> mc(n + 1, vector<int>(targetAmount + 1, 123121));
        for (int i = n; i >= 0; --i) {
            for (int target = 0; target <= targetAmount; ++target) {
                if (target == 0) {
                    mc[i][target] = 0;
                    continue;
                }
                if (i == n) {
                    mc[i][target] = -1; //impossible
                    continue;
                }

                int res = INT_MAX;
                int m1 = mc[i + 1][target];
                if (m1 != -1) res = min(res, m1);
                
                int m2 = -1;
                if (coins[i] <= target) m2 = mc[i][target - coins[i]];
                if (m2 != -1) res = min(res, 1 + m2);

                if (res == INT_MAX) res = -1;
                mc[i][target] = res;
            }
        }
        return mc[0][targetAmount];
    }

    int bottomUpSpaceOptimized(int targetAmount) {
        // mc -> mc[i]
        // mcPrev -> mc[i + 1]
        vector<int> mc(targetAmount + 1, 123124);
        vector<int> mcPrev(targetAmount + 1, 123124);
        for (int i = n; i >= 0; --i) {
            for (int target = 0; target <= targetAmount; ++target) {
                if (target == 0) {
                    mc[target] = 0;
                    continue;
                }
                if (i == n) {
                    mc[target] = -1; //impossible
                    continue;
                }

                int res = INT_MAX;
                int m1 = mcPrev[target];
                if (m1 != -1) res = min(res, m1);
                
                int m2 = -1;
                if (coins[i] <= target) m2 = mc[target - coins[i]];
                if (m2 != -1) res = min(res, 1 + m2);

                if (res == INT_MAX) res = -1;
                mc[target] = res;
            }
            // shift pointers
            mcPrev = mc;
        }
        return mc[targetAmount];
    }

    int coinChange(vector<int>& coins, int amount) {
        this->coins = coins;
        n = coins.size();

        // memo = vector<vector<int>>(n, vector<int>(amount + 1, INT_MIN));
        // return mc(0, amount);    

        // return bottomUp(amount);
        return bottomUpSpaceOptimized(amount);
    }
};
