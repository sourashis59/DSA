class Solution {
    public:
 
    int *weight;
    int *val;
    int n;
    
    vector<vector<int>> memo;
    
    
    //mv(i, c) = max value from val[i...end] with max capacity {c}
    int mv(int i, int c) {
        if (i == n) return 0;
        if (memo[i][c] != -1) return memo[i][c];
        
        //dont pick
        int m1 = mv(i + 1, c);
        //pick if possible
        int m2 = 0;
        if (weight[i] <= c) m2 = val[i] +  mv(i + 1, c - weight[i]);
        
        return memo[i][c] = max(m1, m2);
    }
    
    /*
    Here {i} and {c} are not dependent on each other. So we can swap the for loops:
    
    for (int i = n; i >= 0; --i) {
        for (int c = 0; c <= maxCap; ++c) {
            |
            | can be changed to.
            | both will give correct ans.
            V
            
    for (int c = 0; c <= maxCap; ++c) {
        for (int i = n; i >= 0; --i) {
    */
    int bottomUp(int maxCap) {
        vector<vector<int>> mv = vector<vector<int>>(n + 1, vector<int>(maxCap + 1, -1));
        for (int i = n; i >= 0; --i) {
            for (int c = 0; c <= maxCap; ++c) {
                //base case
                if (i == n) {
                    mv[i][c] = 0;
                    continue;
                }
                
                //dont pick
                int m1 = mv[i + 1][c];
                //pick if possible
                int m2 = 0;
                if (weight[i] <= c) m2 = val[i] +  mv[i + 1][c - weight[i]];
                
                mv[i][c] = max(m1, m2);
            }
        }
        return mv[0][maxCap];
    }
    
    int bottomUpSpaceOptimized(int maxCap) {
        // mv -> mv[i]
        // mvPrev -> mv[i + 1]
        vector<int> mv(maxCap + 1, - 1);
        vector<int> mvPrev(maxCap + 1, -1);
        for (int i = n; i >= 0; --i) {
            for (int c = 0; c <= maxCap; ++c) {
                if (i == n) {
                    mv[c] = 0;
                    continue;
                }
                
                //dont pick
                int m1 = mvPrev[c];
                //pick if possible
                int m2 = 0;
                if (weight[i] <= c) m2 = val[i] +  mvPrev[c - weight[i]];
                
                mv[c] = max(m1, m2);
            }
            // shift pointers
            mvPrev = mv;
        }
        return mv[maxCap];
    }
    
    //Function to return max value that can be put in knapsack of capacity W.
    int knapSack(int W, int wt[], int val[], int n) 
    {        

       // Your code here
        this->weight = wt;
        this->val = val;
        this->n = n;
        
        return bottomUpSpaceOptimized(W);

        return bottomUp(W);
        
        memo = vector<vector<int>>(n, vector<int>(W + 1, -1));
        return mv(0, W);
    }
};
