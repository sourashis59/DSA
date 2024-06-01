//Name: SOURASHIS MONDAL

#include<bits/stdc++.h>

using namespace std;



//*Supports range addition update
class SegmentTree
{
    class Node
    {
    public:
        long long val; //*value of the node
        long long addVal; //*value to be added to the range (range update) -> Lazy Propagation

        Node *left, *right; //*left child and right child
        int low, high; //*this node stores the value of arr[low...high]

    public:
        Node(int val = -1, Node *left = nullptr, Node *right = nullptr, int low = -1, int high = -1) 
            : val(val), addVal(0), left(left), right(right), low(low), high(high)
        {}
    };


private:
    //*root of the segment tree
    Node *root;

    //*mutable array reference (SegmentTree Object will not modify the arr)
    const vector<long long> &arr;
    
    //*size of the array
    int n;

    //*combine function
    std::function<int(int,int)> combine;


public:
    SegmentTree(const vector<long long> &arr, const std::function<int(int,int)>& combine) : arr(arr), combine(combine)
    {
        n = arr.size();
        root = buildTree(0, n-1);
    }



    //*returns the range query value of arr[queryLow, queryHigh]
    int rangeQuery(int queryLow, int queryHigh)
    {
        return rangeQueryHelper(root, queryLow, queryHigh);
    }

    //*changes the value of arr[pos] to newVal
    void update(int pos, int newVal)
    {
        updateHelper(root, pos, newVal);
    }

    //*adds the <val> to all element in the range arr[qlow...qhigh]
    void rangeAddition(int qlow, int qhigh, int val)
    {
        rangeAdditionHelper(root, qlow, qhigh, val);
    }

private:


    // //*TODO: pass the combine() function to the constructor
    // //*combines the values of 2 segments 
    // int combine(int val1, int val2)
    // {
    //     return min(val1, val2);
    // } 



    //*builds segment tree for arr[low...high] and returns the root of the tree
    Node *buildTree(int low, int high)
    {
        Node *root = new Node();
        root->low = low;
        root->high = high;

        //*for leaf node
        if(low == high)
        {
            //*TODO: write function for leaf values
            root->val = arr[low];
            return root;
        }

        int mid = low + (high - low)/2;
        root->left = buildTree(low, mid);
        root->right = buildTree(mid+1, high);

        //*get the value of current node by combining values of left and right child
        root->val = combine(root->left->val, root->right->val);

        return root;
    }


    //*rangeQueryHelper(qlow, qhigh) = returns the value of the range query [qlow, qhigh] from the segment tree rooted at <root> 
    long long rangeQueryHelper(Node* root, int qlow, int qhigh)
    {
        //*if current tree segment is outside query segment
        if(root->low > qhigh || root->high < qlow)
            return LONG_LONG_MIN;

        long long res = 0;

        //*leaf node, or, if tree segment equals query segment
        if(root->low == root->high || (root->low == qlow && root->high == qhigh))
            res = root->val;
        else
        {
            int mid = root->low + (root->high - root->low)/2;

            //*if query segment lies in one of the 2 children
            if(qhigh <= mid)
                res = rangeQueryHelper(root->left, qlow, qhigh);
            else if(qlow >= mid+1)
                res = rangeQueryHelper(root->right, qlow, qhigh);

            //*else if the 2 children segments overlap with the query segment, then answer is to be combined from both subtrees
            else //*if(qlow <= mid && qhigh >= mid+1)
            {
                long long leftVal = rangeQueryHelper(root->left, qlow, mid);
                long long rightVal = rangeQueryHelper(root->right, mid+1, qhigh);
                
                if(leftVal == LONG_LONG_MIN || rightVal == LONG_LONG_MIN)
                    return LONG_LONG_MIN;
                    
                res = combine(leftVal, rightVal);
            }
        }

        //*add the value to be added to the range [Lazy Propagation]
        if(root->addVal != 0)
            res += (qhigh - qlow + 1) * root->addVal;

        return res;
    }

 

    //*updates the value of arr[pos] to newVal, in the segment tree rooted at <root>
    void updateHelper(Node *root, int pos, long long newVal)
    {
        //*for leaf 
        if(root->low == root->high)
        {
            root->val = newVal;
            return;
        }

        //*update that subtree, in which the arr[pos] exists
        int mid = root->low + (root->high - root->low)/2;
        if(pos <= mid)
            updateHelper(root->left, pos, newVal);
        else
            updateHelper(root->right, pos, newVal);

        //*update the value of the current node
        root->val = combine(root->left->val, root->right->val);        
    }


    //*rangeAddition(root, qlow, qhigh, val) -> 
    //*adds <val> to all elements in the range arr[qlow...qhigh] in the segment tree rooted at <root> 
    void rangeAdditionHelper(Node *root, int qlow, int qhigh, long long val)
    {
        //*leaf node, or, if tree segment equals query segment
        if(root->low == root->high || (root->low == qlow && root->high == qhigh))
        {
            root->addVal += val;
            return;
        }

        int mid = root->low + (root->high - root->low)/2;
        if(qhigh <= mid)
            rangeAdditionHelper(root->left, qlow, qhigh, val);
        else if(qlow >= mid+1)
            rangeAdditionHelper(root->right, qlow, qhigh, val);

        //*else if the 2 children segments overlap with the query segment,
        else //*if(qlow <= mid && qhigh >= mid+1)
        {
            rangeAdditionHelper(root->left, qlow, mid, val);
            rangeAdditionHelper(root->right, mid+1, qhigh, val);
        }
    } 

};


long long sum(long long val1, long long val2)
{
    return val1 + val2;
}


int main()
{
    cout << "\n\nHello earth\n\n\n";

    vector<long long> arr = {1,2,3,4,5};
    int n = arr.size();

    SegmentTree st(arr, sum);



    cout<<"\n\n\nend\n";
    return 0;
}