#include<bits/stdc++.h>
using namespace std;

class Solution {

    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }


    //n = current size of the heap 
    void sink(int i, int n, vector<int> &a) {
        while (left(i) < n) {
            int l = left(i), r = right(i);
            int maxInd = i;
            if (l < n && less(a[maxInd], a[l])) maxInd = l;
            if (r < n && less(a[maxInd], a[r])) maxInd = r;
            if (maxInd == i) break;
            swap(a[maxInd], a[i]);
            i = maxInd;
        }
    }

    int top(vector<int> &a) {
        return a[0];
    }

    void buildHeap(vector<int> &a) {
        for (int i = a.size() / 2; i >= 0; --i) {
            sink(i, a.size(), a);
        }
    }
    
public:
    bool less(int a, int b) {
        return a < b;
    }

    vector<int> sortArray(vector<int>& a) {
        int n = a.size();
        buildHeap(a);
        for (int i = n - 1; i >= 0; --i) {
            //delete max and put it at i-th index
            swap(a[i], a[0]);
            sink(0, i, a);
        }

        return a;    
    }
};


int main() {
    Solution ob;
    vector<int> a = {5, 2, 3, 1};
    ob.sortArray(a);
}