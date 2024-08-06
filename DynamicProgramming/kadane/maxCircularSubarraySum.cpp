// https://leetcode.com/problems/maximum-sum-circular-subarray/



//Method1:
/*
Time = O(N)
Space = O(1)

Then 
res = {max sum of linear subarray, max sum subarray starting from 0-th index + max sum subarray ending at (n-1)-th index}

*/




// Method2:
/*
Time = O(N)
Space = O(1)

*/
class Solution {
public:
    vector<int> getTotalSumMaxSumMinSum(const vector<int>& a) {
        int currMaxSum = 0;
        int currMinSum = 0;
        int maxSum = INT_MIN;
        int minSum = INT_MAX;
        int totalSum = 0;
        for (int x: a) {
            if (currMaxSum < 0) currMaxSum = 0;
            if (currMinSum > 0) currMinSum = 0;
            currMaxSum += x;
            currMinSum += x;
            maxSum = max(maxSum, currMaxSum);
            minSum = min(minSum, currMinSum);

            totalSum += x;
        }
        return {totalSum, maxSum, minSum};
    }

    int maxSubarraySumCircular(vector<int>& a) {
        vector<int> temp = getTotalSumMaxSumMinSum(a);
        int totalSum = temp[0];
        int maxSubarrSum = temp[1];
        int minSubarrSum = temp[2];

        // printf("\nmaxSum=%d, minSum=%d, totalSum=%d", maxSum, minSum, totalSum);
        int res = maxSubarrSum;
        if (totalSum != minSubarrSum) res = max(res, totalSum - minSubarrSum);
        return res;
    }
};
