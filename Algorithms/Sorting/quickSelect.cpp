class Solution {
public:
    int partition(int low, int high, vector<int> &a) {
        int pivot = a[low];
        int i = low + 1, j = high;
        while (i <= j) {
            if (a[i] < pivot) ++i;
            else if (a[j] > pivot) --j;
            else if (i <= j) swap(a[i++], a[j--]);
        }
        if (a[low] > a[j]) swap(a[low], a[j]);
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
    
    void quickSelectTopDown(vector<int>& nums, int k) {
        shuffle(nums);
        quickSelect(0, nums.size() - 1, nums, k);    
    }


    // ------------------ BOTTOM-UP --------------------------------//
    void quickSelectBottomUp(int k, vector<int> &arr) {
        shuffle(arr);
        int low = 0, high = arr.size() - 1;
        while (low < high) {
            int p = partition(low, high, arr);
            if (p == k) return;
            else if (p < k) low = p + 1;
            else high = p - 1;
        }
    }
};
