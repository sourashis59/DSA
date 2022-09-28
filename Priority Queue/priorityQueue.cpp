// Name: SOURASHIS MONDAL

#include <bits/stdc++.h>

using namespace std;

class MyHeap
{
private:
    vector<int> arr;
    int size;

private:
    // returns parent node's index of given nodeIndex
    int parentIndex(int nodeIndex);

    // returns left child's index of given nodeIndex
    int leftChildIndex(int nodeIndex);

    // returns right child's index of given nodeIndex
    int rightChildIndex(int nodeIndex);

    /*
        given a complete binary tree with root as nodeIndex and both of its children as heap , percolate the root data down its children
        if the root node doesnt satisfy heap property inorder to heapify the whole tree
    */
    void percolateDown(int nodeIndex);

    /*
        given a heap , percolate the nodeIndex up its ancestors
        until the node data satisfy heap property, inorder to heapify the whole tree
    */
    void percolateUp(int nodeIndex);

public:
    MyHeap();

    // returns the size of the heap
    int getSize();

    // checks if heap is empty or not
    bool isEmpty();

    // inserts data into heap
    void insert(int data);

    // returns the top element of heap (max element for max heap and min element for min heap)
    int top();

    // removes and returns the top element of heap (max element for max heap and min element for min heap)
    int removeTop();

    // prints the heap in sorted order
    void print();

    friend void heapSort(vector<int> &arr);

    friend MyHeap buildHeap(const vector<int> &arr);
};

MyHeap::MyHeap()
{
    this->size = 0;
}

int MyHeap::getSize()
{
    return this->size;
}

bool MyHeap::isEmpty()
{
    return this->size == 0;
}

int MyHeap::top()
{
    if (this->size == 0)
        throw range_error("MyHeap.top() on an empty object :)");

    return this->arr[0];
}

int MyHeap::parentIndex(int nodeIndex)
{

    // out of bound
    if (nodeIndex < 0 || nodeIndex >= this->size)
        return -1;
    // for root node parent is not possible
    else if (nodeIndex == 0)
        return -1;
    else
        return (nodeIndex - 1) / 2;
}

int MyHeap::leftChildIndex(int nodeIndex)
{
    // out of bound
    if (nodeIndex < 0 || nodeIndex >= this->size)
        return -1;

    int l = nodeIndex * 2 + 1;

    return l < this->size ? l : -1;
}

int MyHeap::rightChildIndex(int nodeIndex)
{
    // out of bound
    if (nodeIndex < 0 || nodeIndex >= this->size)
        return -1;

    int r = nodeIndex * 2 + 2;

    return r < this->size ? r : -1;
}

void MyHeap::percolateDown(int nodeInd)
{
    int leftChildInd = leftChildIndex(nodeInd);
    int rightChildInd = rightChildIndex(nodeInd);

    if (leftChildInd == -1 && rightChildInd == -1)
        return;

    int maxInd = nodeInd;

    if (leftChildInd != -1 && this->arr[leftChildInd] > this->arr[maxInd])
        maxInd = leftChildInd;

    if (rightChildInd != -1 && this->arr[rightChildInd] > this->arr[maxInd])
        maxInd = rightChildInd;

    if (maxInd != nodeInd)
    {
        swap(this->arr[nodeInd], this->arr[maxInd]);
        percolateDown(maxInd);
    }
}

void MyHeap::percolateUp(int nodeInd)
{
    int parentInd = parentIndex(nodeInd);

    // if current node has parent and parent and current node are not in correct order then push the current node to up by swapping
    // and similarly do the same for the ancestor nodes
    if (parentInd != -1 && !(this->arr[parentInd] > this->arr[nodeInd]))
    {
        swap(this->arr[parentInd], this->arr[nodeInd]);
        percolateUp(parentInd);
    }
}

void MyHeap::insert(int data)
{
    this->arr.push_back(data);

    this->size++;

    int nodeInd = this->size - 1;

    percolateUp(nodeInd);
}

int MyHeap::removeTop()
{
    if (this->size == 0)
        throw range_error("MyHeap.removeTop() on an empty object :)");

    // swap the root with the last node and delete that last node ,and heapify the heap with percolating the root node down
    int tempData = this->arr[0];
    int lastInd = this->size - 1;
    swap(this->arr[0], this->arr[lastInd]);

    this->size--;
    arr.pop_back();

    percolateDown(0);

    return tempData;
}

MyHeap buildHeap(const vector<int> &arr)
{
    MyHeap h;
    for (auto x : arr)
        h.arr.push_back(x);

    h.size = h.arr.size();

    int n = h.size;
    for (int i = n / 2; i >= 0; i--)
        h.percolateDown(i);

    return h;
}
void heapSort(vector<int> &arr)
{
    MyHeap h = buildHeap(arr);

    int n = arr.size();
    for (int i = n - 1; i >= 0; i--)
    {
        int x = h.removeTop();
        arr[i] = x;
    }
}

void MyHeap::print()
{
    cout << "\nHeap : ";

    if (this->isEmpty())
        cout
            << "Heap is empty :)\n";

    vector<int> tempArr;
    while (!this->isEmpty())
    {
        int data = this->removeTop();
        tempArr.push_back(data);
        cout << data << " , ";
    }

    for (auto x : tempArr)
        this->insert(x);

    // for (int i = 0; i < this->size; i++)
    //     cout << this->arr[i] << " , ";
}

int main()
{
    cout << "\n\nHello earth\n\n\n";

    MyHeap h;

    cout << "\nhhello friends\n";

    h.insert(2);
    // h.print();
    h.insert(4);
    // h.print();
    h.insert(6);
    // h.print();
    h.insert(1);
    h.print();
    h.insert(10);
    h.print();
    h.insert(9);
    h.print();
    h.insert(7);
    h.print();
    h.insert(8);
    h.print();
    h.insert(3);
    h.print();
    h.insert(5);
    h.print();

    cout << "\ntop = " << h.removeTop();
    h.print();

    cout << "\nsize = " << h.getSize();

    cout << "\ntop = " << h.removeTop();
    h.print();

    cout << "\nsize = " << h.getSize();

    cout << "\ntop = " << h.removeTop();
    h.print();

    cout << "\nsize = " << h.getSize();

    cout << "\ntop = " << h.removeTop();
    h.print();

    cout << "\nsize = " << h.getSize();

    // MyHeap h2;

    // h2.removeTop();

    vector<int> arr = {10, 7, 5, 9, 2, 3, 1, 4, 6, 8};
    heapSort(arr);

    cout << "\n\narr : ";
    for (int x : arr)
        cout << x << " ";

    cout << "\n\n\n\nBYE WOrld\n\n";

    return 0;
}