//Name: SOURASHIS MONDAL

#include<bits/stdc++.h>

using namespace std;

class SegmentTree {
private:
    //arry of size 4n to store the tree
    //leftChild(i) = 2i + 1
    //rightChild(i) = 2i + 2
    vector<long long> t;
    //size of the actual array(range)
    int n;

public:
    SegmentTree(const vector<long long> &arr) {
        n = arr.size();
        t = vector<long long> (4 * n);
        build(0, 0, n - 1, arr);
    }

    long long query(int qlow, int qhigh) {
        return query(0, 0, n - 1, qlow, qhigh);
    }

    void update(int targetArrInd, long long newVal) {
        update(0, 0, n - 1, targetArrInd, newVal);
    }

    //TODO: change according to your need
    //here combine function is: sum
    long long combine(long long x, long long y) {
        return x + y;
    }

private:
    int leftChild(int rootId) { return 2 * rootId + 1;}
    int rightChild (int rootId) { return 2 * rootId + 2;}

    /*
    [tl, th] = [low, high] range of current subtree
    [ql, qh] = [low, high] range of query
    tm = mid of the range of current tree

    REMEMBER: To acess t[], always use node id as index (ex: t[rootId], t[leftId], t[rightId], ...)
                never to use range (ex: tl, tm, th, ql, qh, ....) as index of t[]
    -----------------
    */

    void build(int rootId, int tl, int th, const vector<long long> &arr) {
        //leaf
        if (tl == th) {
            t[rootId] = arr[tl];
            return;
        }

        int tm = tl + (th - tl) / 2;
        int leftId = leftChild(rootId), rightId = rightChild(rootId);
        build(leftId, tl, tm, arr);
        build(rightId, tm + 1, th, arr);
        t[rootId] = combine(t[leftId], t[rightId]); 
    }

    long long query(int rootId, int tl, int th, int ql, int qh) {
        if (tl >= ql && th <= qh) return t[rootId];
        
        int leftId = leftChild(rootId), rightId = rightChild(rootId);
        int tm = tl + (th - tl) / 2;
        if (qh <= tm) return query(leftId, tl, tm, ql, qh);
        else if (ql >= tm + 1) return query(rightId, tm + 1, th, ql, qh);
        else return combine(query(leftId, tl, tm, ql, qh), query(rightId, tm + 1, th, ql, qh));
    }

    void update(int rootId, int tl, int th, int targetArrInd, int newVal) {
        //leaf
        if (tl == th) {
            t[rootId] = newVal;
            return;
        } 
        int leftId = leftChild(rootId), rightId = rightChild(rootId);
        int tm = tl + (th - tl) / 2;
        
        //update the child subtree
        if (targetArrInd <= tm) update(leftId, tl, tm, targetArrInd, newVal);
        else update(rightId, tm + 1, th, targetArrInd, newVal);

        //update the val of current range
        t[rootId] = combine(t[leftId], t[rightId]);        
    }
};

