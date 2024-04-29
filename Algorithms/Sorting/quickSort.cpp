class TwoWayQuickSort {
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

    void quickSort(int low, int high, vector<int> &arr) {
        if (low >= high) return;
        int p = partition(low, high, arr);
        quickSort(low, p - 1, arr);
        quickSort(p + 1, high, arr);
    }

    void shuffle(vector<int> &arr) {
        int n = arr.size();
        for (int i = 0; i < n; ++i) {
            int r = rand() % (i + 1);
            swap(arr[i], arr[r]);
        }
    }

    vector<int> sortArray(vector<int>& nums) {
        shuffle(nums);
        quickSort(0, nums.size() - 1, nums);
        return nums;    
    }
};
