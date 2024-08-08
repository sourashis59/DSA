
// https://www.geeksforgeeks.org/problems/boolean-parenthesization5610/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
class Solution{
    const long P = 1003;
    string a;
    int n;
    
    vector<vector<pair<int, int>>> memo;
    
    
    int posMod(int x, int m) {
        x = x % m;
        if (x < 0) x += m;
        return x;
    }
    
    // returns {#true, #false}
    pair<int, int> getCount(const pair<int, int> &left, const pair<int, int> &right, char currOperator) {
        int totalCount = (
                (left.first * right.first) % P
                + (left.first * right.second) % P
                + (left.second * right.first) % P
                + (left.second * right.second) % P
            ) % P;
        
        int trueCount = 0, falseCount = 0;
        switch (currOperator) {
        case '&':
            trueCount = left.first * right.first % P;
            falseCount = posMod(totalCount - trueCount, P);
            break;
        case '|':
            falseCount = left.second * right.second % P;
            trueCount = posMod(totalCount - falseCount, P);
            break;
        case '^':
            trueCount = (
                    left.first * right.second % P
                    + left.second * right.first % P
                ) % P;
            falseCount = posMod(totalCount - trueCount, P);
        }
        // printf("\ncurrOperator: %c, trueCount=%d, falseCount=%d", currOperator, trueCount, falseCount);
        return {trueCount, falseCount};
    }
    
    // c(i, j) = {no. of parenthesization with true val, no. of ... false val}
    //           from a[i...j]
    pair<int, int> c(int i, int j) {
        if (i == j) return (a[i] == 'T') ? make_pair(1, 0) : make_pair(0, 1);
        if (memo[i][j].first != -1) return memo[i][j];
        
        pair<int, int> res = {0, 0};
        for (int k = i; k < j; k += 2) {
            pair<int, int> left = c(i, k);
            pair<int, int> right = c(k + 2, j);
            pair<int, int> currCount = getCount(left, right, a[k + 1]);
            
            res.first = (res.first + currCount.first) % P;
            res.second = (res.second + currCount.second) % P;
        }
        return memo[i][j] = res;
    }
    
    int bottomUp() {
        vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(n, make_pair(-1, -1)));
        // IMPORTANT: i -= 2 and j += 2, instead of i++ and j--
        for (int i = n - 1; i >= 0; i -= 2) {
            for (int j = i; j < n; j += 2) {
                if (i == j) {
                    c[i][j] = (a[i] == 'T') ? make_pair(1, 0) : make_pair(0, 1);
                    continue;
                }
                pair<int, int> res = {0, 0};
                for (int k = i; k < j; k += 2) {
                    pair<int, int> left = c[i][k];
                    pair<int, int> right = c[k + 2][j];
                    pair<int, int> currCount = getCount(left, right, a[k + 1]);
                    
                    res.first = (res.first + currCount.first) % P;
                    res.second = (res.second + currCount.second) % P;
                }
                c[i][j] = res;
            }
        }
        return c[0][n - 1].first;
    }
    
public:
    int countWays(int n, string s){
        this->a = s;
        this->n = a.size();
        
        // memo = vector<vector<pair<int, int>>>(n, vector<pair<int ,int>>(n, {-1, -1}));
        // return c(0, n - 1).first;
        
        return bottomUp();
    }

};
