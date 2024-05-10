///ALL THE FUNCTIONS ARE FOR MAX HEAP

#include <iostream>
using namespace std;

class PriorityQueue {
private:
    vector<long long> arr;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void swimUp(int i) {
        while (parent(i) >= 0 && arr[i] < arr[parent(i)]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    void swimDown(int i) {
        int minInd = i;
        if (leftChild(i) < arr.size() && arr[leftChild(i)] < arr[minInd]) 
            minInd = leftChild(i);
        if (rightChild(i) < arr.size() && arr[rightChild(i)] < arr[minInd]) 
            minInd = rightChild(i);
        
        if (i != minInd) {
            swap(arr[i], arr[minInd]);
            swimDown(minInd);
        } 
    }

public:
    void push(long long x) {
        arr.push_back(x);
        swimUp(arr.size() - 1);
    }

    long long pop() {
        long long res = arr[0];
        arr[0] = arr.back();
        arr.pop_back();
        swimDown(0);
        return res;
    }

    int size() {
        return arr.size();
    }
};
