class Solution {
public:

    bool less(int a, int b) {
        return a < b;
    }

    void shellSort(vector<int> &a) {
        int n = a.size();
        int h = 1;

        //3x + 1 increment sequence: get the last number of the sequence
        while (h < n / 3) h = 3 * h + 1;

        while (h >= 1) {
            //h-sort the array
            for (int i = h; i < n; ++i) {
                for (int j = i; j >= h; j -= h) {
                    if (less(a[j], a[j - h])) swap(a[j], a[j - h]);
                    else break;
                }
            }
            //get the next smaller h
            h = h / 3;
        }
    }

    vector<int> sortArray(vector<int>& a) {
        shellSort(a);
        return a;    
    }
};
