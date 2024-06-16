class Solution {
public:
    vector<int> aux;

    void merge(int low, int mid, int high, vector<int>  &arr) {
        if (arr[mid] <= arr[mid + 1]) return;

        int i = low, j = mid + 1, k = low;
        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) aux[k++] = arr[i++]; 
            else aux[k++] = arr[j++];
        }
        while (i <= mid) aux[k++] = arr[i++];
        while (j <= high) aux[k++] = arr[j++];
        for (int i = low; i <= high; ++i)
            arr[i] = aux[i];
    }

    void mergeSort(int low, int high, vector<int> &arr) {
        if (low >= high) return;
        int mid = low + (high - low) / 2;
        mergeSort(low, mid, arr);
        mergeSort(mid + 1, high, arr);
        merge(low, mid, high, arr);
    }

    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        aux = vector<int>(n);
        mergeSort(0, n - 1, nums);
        return nums;
    }
};
