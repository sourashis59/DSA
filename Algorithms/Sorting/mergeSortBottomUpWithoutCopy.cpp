#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool less(int a, int b) {
        return a < b;
    }

    //merges a[low...mid] and a[mid+1...high] into aux[low...high]
    void merge(int low, int mid, int high, vector<int>  &a, vector<int> &aux) {
        //CHANGE: must copy to from a to aux. So comment this line:
        // if (a[mid] <= a[mid + 1]) return;

        int i = low, j = mid + 1, k = low;
        while (i <= mid && j <= high) {
            if (less(a[i], a[j])) aux[k++] = a[i++]; 
            else aux[k++] = a[j++];
        }
        while (i <= mid) aux[k++] = a[i++];
        while (j <= high) aux[k++] = a[j++];
        
        //CHANGE: dont copy
        // for (int i = low; i <= high; ++i) a[i] = aux[i];
    }


    void mergeSort(int low, int high, vector<int> &a) {
        int n = a.size();
        vector<int> aux(n);

        int level = 1;
        for (int halfSize = 1; halfSize < n; halfSize *= 2) {
            //merge 2 halves, till left half(part) exists [i.e. low < n]
            for (int low = 0; low < n; low += 2 * halfSize) {
                int mid = min(n - 1, low + halfSize - 1);
                int high = min(n - 1, mid + halfSize);

                //CHANGE: at odd level, merge a[low...mid] and a[mid+1...high] into aux[low...high]
                //and at even level do the opposite    
                if (level % 2 == 1) merge(low, mid, high, a, aux);
                else                 merge(low, mid, high, aux, a);                 
            }
            ++level;            
        }
        //if level is odd, then aux[] contains the sorted array
        if (level % 2 == 0) {
            for (int i = 0; i < n; ++i) 
                a[i] = aux[i];
        }
    }

    vector<int> sortArray(vector<int>& a) {
        mergeSort(0, a.size() - 1, a);
        return a;    
    }
};






int main() {
    vector<int> a = {10, 2, 3, 7, 15, 9};
    Solution ob;
    ob.sortArray(a);

    for (int i = 0; i < 1000; ++i) {
        int n = rand() % 100;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = rand() % 200;

        vector<int> copy = arr;
        vector<int> initArr = arr;
        sort(copy.begin(), copy.end());
        ob.sortArray(arr);

        if (copy != arr) {
            printf("\nnot equal");
            printf("\ninit array:");
            for (int x: initArr) cout << x << ", ";
        }
    }
    printf("\n\nDone\n\n");
}

