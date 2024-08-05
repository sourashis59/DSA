class Solution
{
    int n1, n2, n3;
    string s1, s2, s3;
    
public:
    
    
    int bottomUp() {
        // l(i, j, k) = length of lcs of s1[i...end], s2[j...end], s3[k...end]
        vector<vector<vector<int>>> l(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1)));
        for (int i = n1; i >= 0; --i) {
            for (int j = n2; j >= 0; --j) {
                for (int k = n3; k >= 0; --k) {
                    if (i == n1 || j == n2 || k == n3) {
                        l[i][j][k] = 0;
                        continue;
                    }    
                    
                    int res = 0;
                    if (s1[i] == s2[j] && s2[j] == s3[k]) res = 1 + l[i + 1][j + 1][k + 1];
                    else res = max({
                                    l[i][j][k + 1],
                                    l[i][j + 1][k],
                                    // l[i][j + 1][k + 1],
                                    l[i + 1][j][k],
                                    // l[i + 1][j][k + 1],
                                    // l[i + 1][j + 1][k]
                        
                                });
                    
                    l[i][j][k] = res;
                }
            }
        }
        return l[0][0][0];
    }

    int bottomUpSpaceOptimized() {
        // Rule: Replace each l[i] with l and l[i+1] with lprev and shift pointers after i's loop
        // l -> l[i]
        // lprev -> l[i+1]
        vector<vector<int>> l(n2 + 1, vector<int>(n3 + 1));
        vector<vector<int>> lprev(n2 + 1, vector<int>(n3 + 1));
        for (int i = n1; i >= 0; --i) {
            for (int j = n2; j >= 0; --j) {
                for (int k = n3; k >= 0; --k) {
                    if (i == n1 || j == n2 || k == n3) {
                        l[j][k] = 0;
                        continue;
                    }    
                    
                    int res = 0;
                    if (s1[i] == s2[j] && s2[j] == s3[k]) res = 1 + lprev[j + 1][k + 1];
                    else res = max({
                                    l[j][k + 1],
                                    l[j + 1][k],
                                    lprev[j][k],
                                });
                    
                    l[j][k] = res;
                }
            }
            // shift pointers
            lprev = l;
        }
        return l[0][0];
    }
    
    int LCSof3 (string A, string B, string C, int n1, int n2, int n3) {
        s1 = A, s2 = B, s3 = C;
        this->n1 = n1;
        this->n2 = n2;
        this->n3 = n3;
        
        return bottomUp();    
        
    }
};
