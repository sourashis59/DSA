//Name: SOURASHIS MONDAL

#include<bits/stdc++.h>

using namespace std;

class SegmentTree {
private:
    //arry of size 4n to store the tree
    //leftChild(i) = 2i + 1
    //rightChild(i) = 2i + 2
    vector<long long> tree;
    //size of the actual array(range)
    int n;

public:
    SegmentTree(const vector<long long> &arr) {
        n = arr.size();
        tree = vector<long long> (4 * n);
        build(0, 0, n - 1, arr);
    }

    long long rangeQuery(int qlow, int qhigh) {
        return rangeQuery(0, 0, n - 1, qlow, qhigh);
    }

    void updateInd(int ind, long long newVal) {
        updateInd(0, 0, n - 1, ind, newVal);
    }

    //TODO: change according to your need
    //here combine function is: sum
    long long combine(long long x, long long y) {
        return x + y;
    }

private:
    int leftChild(int rootId) { return 2 * rootId + 1;}
    int rightChild (int rootId) { return 2 * rootId + 2;}

    //build(rootId, low, high) = builds the segment tree rooted at rootId with range of root as [low, high]
    void build(int rootId, int low, int high, const vector<long long> &arr) {
        //for leaf
        if (low == high) {
            tree[rootId] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        int leftId = leftChild(rootId), rightId = rightChild(rootId);
        build(leftId, low, mid, arr);
        build(rightId, mid + 1, high, arr);
        tree[rootId] = combine(tree[leftId], tree[rightId]);
    }

    // no need to change qlow, qhigh in recursive calls
    // rootId = root of the current segment tree
    // [rlow, rhigh] = range of the root of the current tree
    long long rangeQuery(int rootId, int rlow, int rhigh, int qlow, int qhigh) {
        if (rlow >= qlow && rhigh <= qhigh) return tree[rootId];
        
        int leftId = leftChild(rootId), rightId = rightChild(rootId);
        int rmid = rlow + (rhigh - rlow) / 2;
        if (qhigh <= rmid) return rangeQuery(leftId, rlow, rmid, qlow, qhigh);
        if (qlow >= rmid + 1) return rangeQuery(rightId, rmid + 1, rhigh, qlow, qhigh);
        else return combine(rangeQuery(leftId, rlow, rmid, qlow, qhigh),
                            rangeQuery(rightId, rmid + 1, rhigh, qlow, qhigh));
    }

    // no need to change qlow, qhigh in recursive calls
    void updateInd(int rootId, int rlow, int rhigh, int ind, long long newVal) {
        //leaf
        if (rlow == rhigh) {
            tree[rootId] = newVal;
            return;
        }
        int leftId = leftChild(rootId), rightId = rightChild(rootId);
        int rmid = rlow + (rhigh - rlow) / 2;
        if (ind <= rmid) updateInd(leftId, rlow, rmid, ind, newVal);
        else updateInd(rightId, rmid + 1, rhigh, ind, newVal);
        //update current range val
        tree[rootId] = combine(tree[leftId], tree[rightId]);
    }
};
