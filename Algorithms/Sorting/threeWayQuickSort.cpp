
class Solution {
public:
    //partitions w.r.t a[low] (=v) and returns {lt, gt} indcies, such that 
    //a[low...(lt-1)] < v
    //a[lt...gt] == v
    //a[(gt+1)...high] > v
    pair<int, int> threeWayPartition(int low, int high, vector<int> &a) {
        int v = a[low];
        int lt = low, i = low, gt = high;
        while (i <= gt) {
            if (a[i] == v) ++i;
            else if (a[i] < v) swap(a[lt++], a[i++]);
            else swap(a[i], a[gt--]);
        } 
        return {lt, gt};
    }

    void quickSort(int low, int high, vector<int> &arr) {
        if (low >= high) return;
        auto [lt, gt] = threeWayPartition(low, high, arr);
        quickSort(low, lt - 1, arr);
        quickSort(gt + 1, high, arr);
    }

    void shuffle(vector<int> &arr) {
        int n = arr.size();
        for (int i = 0; i < n; ++i) {
            int r = rand() % (i + 1);
            swap(arr[i], arr[r]);
        }
    }

    vector<int> sortArray(vector<int>& a) {
        shuffle(a);
        quickSort(0, a.size() - 1, a);
        return a;    
    }
};
