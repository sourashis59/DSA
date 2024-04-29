class Solution {
public:
    int partition(int low, int high, vector<int> &arr) {
        int pivot = arr[low];
        int i = low + 1, j = high;
        while (i <= j) {
            //SOME EDGE CONDITION: 
            //DONT PUT EQUAL HERE --> IT WILL BE SLOWER (PARTITIONING WILL BE BAD)
            //IF MOST ELEMENTS ARE EQUAL 
            if (arr[i] < pivot) ++i;
            else if (arr[j] > pivot) --j;
            else swap(arr[i++], arr[j--]); 
        }
        swap(arr[j], arr[low]);
        return j;
    }

    int quickSelect(int low, int high, vector<int> &arr, int k) {
        if (low >= high) return low;
        int p = partition(low, high, arr);
        if (p == k) return p;
        else if (p > k) return quickSelect(low, p - 1, arr, k);
        else return quickSelect(p + 1, high, arr, k);
    }

    void shuffle(vector<int> &arr) {
        int n = arr.size();
        for (int i = 0; i < n; ++i) {
            int r = rand() % (i + 1);
            swap(arr[i], arr[r]);
        }
    }
    
    //returns index
    int quickSelect(vector<int>& nums, int k) {
        // shuffle(nums);
        return quickSelect(0, nums.size() - 1, nums, k);    
    }
};
