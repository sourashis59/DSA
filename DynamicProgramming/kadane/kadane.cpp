class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int currSum = 0;
        int res = INT_MIN;
        for (int x: nums) {
            if (currSum < 0) currSum = 0;
            currSum += x;
            res = max(res, currSum);
        }
        return res;
    }
};
