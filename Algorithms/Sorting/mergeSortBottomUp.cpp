class Solution {
public:
    bool less(int a, int b) {
        return a < b;
    }

    void merge(int low, int mid, int high, vector<int>  &a, vector<int> &aux) {
        if (a[mid] <= a[mid + 1]) return;
        int i = low, j = mid + 1, k = low;
        while (i <= mid && j <= high) {
            if (less(a[i], a[j])) aux[k++] = a[i++]; 
            else aux[k++] = a[j++];
        }
        while (i <= mid) aux[k++] = a[i++];
        while (j <= high) aux[k++] = a[j++];
        //copy
        for (int i = low; i <= high; ++i) a[i] = aux[i];
    }

    void mergeSort(int low, int high, vector<int> &a, vector<int> &aux) {
        int n = a.size();
        for (int halfSize = 1; halfSize < n; halfSize *= 2) {
            //merge 2 halves, till 2nd half exists [i.e. (mid + 1) < n]
            for (int low = 0; low < n; low += 2 * halfSize) {
                int mid = min(n - 1, low + halfSize - 1);
                int high = min(n - 1, mid + halfSize);
                merge(low, mid, high, a, aux); 
            }
        }
    }

    vector<int> sortArray(vector<int>& a) {
        vector<int> aux(a.size());
        mergeSort(0, a.size() - 1, a, aux);
        return a;    
    }
};
