// https://leetcode.com/problems/coin-change-ii/
class Solution {
public:
    vector<int> coins;
    int n;

    vector<vector<int>> memo;

    long long c(int i, int target) {
        if (target == 0) return 1;
        if (i == n) return 0;
        if (memo[i][target] != -1) return memo[i][target];

        long long res = 0;
        res += c(i + 1, target);
        if (coins[i] <= target) res += c(i, target - coins[i]);
        return memo[i][target] = res;
    }

    long long bottomUp(int amount) {
        vector<vector<long long>> c(n + 1, vector<long long>(amount + 1, -1));
        for (int i = n; i >= 0; --i) {
            for (int target = 0; target <= amount; ++target) {
                if (target == 0) {
                    c[i][target] = 1;
                    continue;
                }
                if (i == n) {
                    c[i][target] = 0;
                    continue;
                }

                long long res = 0;
                res += c[i + 1][target];
                if (coins[i] <= target) res += c[i][target - coins[i]];
                c[i][target] = res;               
            }
        }
        return c[0][amount];
    } 

    long long bottomUpSpaceOptimized(int amount) {
        // c -> c[i]
        // cprev -> c[i + 1]
        vector<long long> c(amount + 1, -1);
        vector<long long> cprev(amount + 1, -1);
        for (int i = n; i >= 0; --i) {
            for (int target = 0; target <= amount; ++target) {
                if (target == 0) {
                    c[target] = 1;
                    continue;
                }
                if (i == n) {
                    c[target] = 0;
                    continue;
                }

                long long res = 0;
                res += cprev[target];
                if (coins[i] <= target) res += c[target - coins[i]];
                c[target] = res;               
            }
            // shift pointers
            cprev = c;
        }
        return c[amount];
    } 


    int change(int target, vector<int>& coins) {
        this->coins = coins;
        n = coins.size();   


        // memo = vector<vector<int>>(n, vector<int>(target + 1, -1));
        // return c(0, target);

        // return bottomUp(target);
        return bottomUpSpaceOptimized(target);

    }
};
