class Solution {
public:

    bool less(int a, int b) {
        return a < b;
    }

    void insertionSort(vector<int> &a) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i; j > 0; --j) {
                if (less(a[j], a[j - 1])) swap(a[j], a[j - 1]);
                else break;
            }
        }
    }

    vector<int> sortArray(vector<int>& a) {
        insertionSort(a);
        return a;    
    }
};
