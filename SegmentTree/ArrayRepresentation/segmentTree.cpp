//Name: SOURASHIS MONDAL

#include<bits/stdc++.h>

using namespace std;

class SegmentTree
{
    //*we will store the segment tree using an array of size 4n
    
    //*internal array to store the tree
    int *t;

    //*size of the internal array 't'
    int size;

    //*size of the original array
    int n;

    //*combine function
    std::function<int(int,int)> combine;


private:

    //*returns the index of the left child of the node with index i
    int leftChildInd(int i)
    {
        return 2*i + 1;
    }

    //*returns the index of the right child of the node with index i
    int rightChildInd(int i)
    {
        return 2*i + 2;
    }

    // //*TODO: pass the combine() function to the constructor
    // //*combines the values of 2 segments 
    // int combine(int val1, int val2)
    // {
    //     return min(val1, val2);
    // } 

    //*buildTree(ind, low, high) --> builds the segment tree with root vertex at index ind, and 
    //*                            segment index from low to high
    void buildTree(int ind, int low, int high, int arr[])
    {
        //*for leaf node
        if(low == high)
        {
            //*TODO: write function for leaf values
            this->t[ind] = arr[low];
            return; 
        }

        int mid = low + (high - low)/2;
        int l = leftChildInd(ind);
        int r = rightChildInd(ind);

        //*build left and right subtrees recursively
        buildTree(l, low, mid, arr);
        buildTree(r, mid+1, high, arr);

        //*get the value of current node by combining values of left and right child
        this->t[ind] = combine(t[l], t[r]); 
    }



    //*returns the value of the range query with root at index ind and segment range [treeLow, treeHigh]
    //*and query range : [queryLow, queryHigh]
    int rangeQueryHelper(int ind, int treeLow, int treeHigh, int queryLow, int queryHigh)
    {
        //*leaf node
        if(treeLow == treeHigh)
            return t[ind];

        //*if tree node segment is same as query segment, then that node contains the answer of that query
        if(treeLow == queryLow && treeHigh == queryHigh)
            return t[ind];

        int treeMid = treeLow + (treeHigh - treeLow)/2;

        //*if query segment lies in one of the 2 children
        if(queryHigh <= treeMid)
            return rangeQueryHelper(leftChildInd(ind), treeLow, treeMid, queryLow, queryHigh);
        else if(queryLow >= treeMid + 1)
            return rangeQueryHelper(rightChildInd(ind), treeMid+1, treeHigh, queryLow, queryHigh);

        //*if the tree node segment overlaps the query segment, then answer is to be combined from both subtrees
        else //if(queryLow <= treeMid && queryHigh >= treeMid + 1)
        {
            int leftVal = rangeQueryHelper(leftChildInd(ind), treeLow, treeMid, queryLow, treeMid);
            int rightVal = rangeQueryHelper(rightChildInd(ind), treeMid+1, treeHigh, treeMid+1, queryHigh);

            return combine(leftVal, rightVal);
        }            
    }

    

    //*updates the value of arr[low] to newVal , with root at index ind and segment range [treeLow, treeHigh]
    void updateValueHelper(int ind, int treeLow, int treeHigh, int pos, int newVal)
    {
        //*for leaf
        if(treeLow == treeHigh)
        {
            t[ind] = newVal;
            return;
        }

        //*update the subtree, where the arr[pos] exists
        int treeMid = treeLow + (treeHigh - treeLow)/2;

        //*left subtree
        if(pos <= treeMid)
            updateValueHelper(leftChildInd(ind), treeLow, treeMid, pos, newVal);
        //*right subtree
        else
            updateValueHelper(rightChildInd(ind), treeMid+1, treeHigh, pos, newVal);

        //*update the value of the current node
        t[ind] = combine(t[leftChildInd(ind)], t[rightChildInd(ind)]);        
    }

public:
    SegmentTree(int arr[], int n, const std::function<int(int,int)>& combine)
    {
        this->n = n;
        this->size = 4*n;
        this->t = new int[size];
        this->combine = combine;

        //*root at index 0
        buildTree(0, 0, n-1, arr);

    }


    //*returns the range query value of arr[quryLow, queryHigh]
    int rangeQuery(int queryLow, int queryHigh)
    {
        return rangeQueryHelper(0, 0, n-1, queryLow, queryHigh);
    }

    //*changes the value of arr[pos] to newVal
    void updateValue(int pos, int newVal)
    {
        updateValueHelper(0, 0, n-1, pos, newVal);
    }
};

int sum(int val1, int val2)
{
    return val1 + val2;
}


int main()
{
    cout << "\n\nHello earth\n\n\n";

    int arr[] = {1,2,3,4,5};
    int n = sizeof(arr)/sizeof(arr[0]);

    SegmentTree st(arr, n, sum );



    cout<<"\n\n\nend\n";
    return 0;
}