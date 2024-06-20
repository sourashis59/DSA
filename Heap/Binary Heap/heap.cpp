#include <iostream>
using namespace std;

// template <typename T>
class Heap {
    vector<int> a;

    int parent(int i) {return (i - 1) / 2;}
    int left(int i) {return 2 * i + 1;}
    int right(int i) {return 2 * i + 2;}

    bool less(int a, int b) {
        return a < b;
    }

    void swim(int i) {
        while (parent(i) >= 0 && less(a[parent(i)], a[i])) {
            swap(a[parent(i)], a[i]);
            i = parent(i);
        }
    }

    void sink(int i) {
        while (left(i) < size()) {
            int l = left(i), r = right(i);
            int maxInd = i;
            if (l < size() && less(a[maxInd], a[l])) maxInd = l;
            if (r < size() && less(a[maxInd], a[r])) maxInd = r;
            if (maxInd == i) break;
            swap(a[maxInd], a[i]);
            i = maxInd;
        }
    }

    // //recursive
    // void sink(int i) {
    //     int maxInd = i;
    //     if (leftChild(i) < arr.size() && arr[leftChild(i)] > arr[minInd]) 
    //         minInd = leftChild(i);
    //     if (rightChild(i) < arr.size() && arr[rightChild(i)] > arr[minInd]) 
    //         minInd = rightChild(i);
        
    //     if (i != minInd) {
    //         swap(arr[i], arr[minInd]);
    //         swimDown(minInd);
    //     } 
    // }

public:
    Heap() {}

    void push(int val) {
        a.push_back(val);
        swim(a.size() - 1);
    }

    void pop() {
        a[0] = a.back();
        a.pop_back();
        sink(0);
    }

    int top() {
        return a[0];
    }

    int size() {
        return a.size();
    }

};
