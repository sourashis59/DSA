//Name: SOURASHIS MONDAL

#include<bits/stdc++.h>

using namespace std;

class SegmentTree {
    class Node {
    public:
        int low, high;
        long long val;
        Node *left, *right;
        Node (int low = -1, int high = -1, long long val = -1, Node *left = nullptr, Node *right = nullptr):
            low(low), high(high), val(val), left(left), right(right) {}
    };

private:
    Node *root;

public:
    SegmentTree(const vector<long long> &arr) {
        root = build(0, arr.size() - 1, arr);
    }

    int rangeQuery(int qlow, int qhigh) {
        return rangeQuery(root, qlow, qhigh);
    }

    void updateInd(int ind, long long newVal) {
        updateInd(root, ind, newVal);
    }

    //TODO: change according to your need
    //here combine function is: sum
    long long combine(long long x, long long y) {
        return x + y;
    }

private:
    Node* build(int low, int high, const vector<long long> &arr) {
        Node *root = new Node(low, high);
        //for leaf
        if (low == high) {
            root->val = arr[low];
            return root;
        }
        int mid = low + (high - low) / 2;
        root->left = build(low, mid, arr);
        root->right = build(mid + 1, high, arr);
        root->val = combine(root->left->val, root->right->val);
        return root;
    }

    long long rangeQuery(Node *root, int qlow, int qhigh) {
        if (root->low >= qlow && root->high <= qhigh) return root->val;
        int mid = root->low + (root->high - root->low) / 2;
        if (qhigh <= mid) return rangeQuery(root->left, qlow, qhigh);
        if (qlow >= mid + 1) return rangeQuery(root->right, qlow, qhigh);
        else return combine(rangeQuery(root->left, qlow, qhigh),
                            rangeQuery(root->right, qlow, qhigh));
    }

    void updateInd(Node *root, int ind, long long newVal) {
        //leaf
        if (root->low == root->high) {
            root->val = newVal;
            return;
        }
        int mid = root->low + (root->high - root->low) / 2;
        if (ind <= mid) updateInd(root->left, ind, newVal);
        else updateInd(root->right, ind, newVal);
        //update current range val
        root->val = combine(root->left->val, root->right->val);
    }
};



int main()
{
    cout << "\n\nHello earth\n\n\n";

    vector<long long> arr = {1,2,3,4,5};
    int n = arr.size();

    SegmentTree st(arr);



    cout<<"\n\n\nend\n";
    return 0;
}
