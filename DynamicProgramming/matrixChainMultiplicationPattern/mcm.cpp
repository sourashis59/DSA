
// https://www.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1
class Solution{
    int *arr;
    int n;
public:
    
    vector<vector<int>> memo;    
    
    // mc(i, j) = min cost to multiply matrix[i...j]
    int mc(int i, int j) {
        // for one matrix
        if (i == j) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        
        int res = INT_MAX;
        for (int k = i; k < j; ++k) {
            int m1 = mc(i, k) + mc(k + 1, j) + arr[i] * arr[k + 1] * arr[j + 1];
            res = min(res, m1);
        }
        return memo[i][j] = res;
    }
    
    
    int bottomUp() {
        vector<vector<int>> mc(n, vector<int>(n, -1));
        for (int i = n - 2; i >= 0; --i) {
            // or, j = 0 to n-2 => will also be correct
            for (int j = i; j <= n - 2; ++j) {
                if (i == j) {
                    mc[i][j] = 0;
                    continue;
                }

                int res = INT_MAX;
                for (int k = i; k < j; ++k) {
                    int m1 = mc[i][k] + mc[k + 1][j] + arr[i] * arr[k + 1] * arr[j + 1];
                    res = min(res, m1);
                }
                mc[i][j] = res;
                // printf("\ni=%d, j=%d, res=%d", i, j, res);
            }
        }
        return mc[0][n - 2];
    }
    
    int matrixMultiplication(int n, int arr[]) {
        this->n = n;
        this->arr = arr;
        
        // memo = vector<vector<int>>(n, vector<int>(n, -1));
        // return mc(0, n - 2);
        
        return bottomUp();
    }
};


