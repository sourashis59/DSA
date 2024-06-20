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

    //returns partition index
    int quickSelect(int low, int high, int k, vector<int> &arr) {
        if (low >= high) return low;
        auto [lt, gt] = threeWayPartition(low, high, arr);
        if (lt <= k && k <= gt) return k;
        else if (k > gt) return quickSelect(gt + 1, high, k, arr);
        else return quickSelect(low, lt - 1, k, arr);
    }


    void shuffle(vector<int> &arr) {
        for (int i = 0; i < arr.size(); ++i) {
            int r = rand() % (i + 1);
            swap(arr[i], arr[r]);
        }
    }

    void quickSelectTopDown(int k, vector<int> &arr) {
        shuffle(arr);
        quickSelect(0, arr.size() - 1, k, arr);
    }

    void quickSelectBottomUp(int k, vector<int> &arr) {
        shuffle(arr);
        int low = 0, high = arr.size() - 1;
        while (low < high) {
            auto [lt, gt] = threeWayPartition(low, high, arr);
            if (lt <= k && k <= gt) return;
            else if (k > gt) low = gt + 1;
            else high = lt - 1;
        }
    }
};
