///ALL THE FUNCTIONS ARE FOR MAX HEAP

#include <iostream>
#define data_type int

using namespace std;

struct Heap
{
    int capacity, count;
    int *arr;
    //int heap_type; // for max heap = 1, for min heap = 0
};

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

///Creates a heap and returns the address
Heap *CreateHeap(int capacity)
{
    Heap *h = new Heap;
    if (h == NULL)
    {
        cout << "\nMemory allocation failed";
        exit(0);
    }

    h->capacity = capacity;
    h->count = 0;
    //h->heap_type = heap_type;

    h->arr = new data_type[h->capacity];
    if (h->arr == NULL)
    {
        cout << "\nMemory allocation failed";
        exit(0);
    }

    return h;
}

///Doubles the capacity of the inputted heap and return the address of the heap
void ResizeHeap(Heap *h)
{
    int *temp = h->arr;
    h->capacity = 2 * h->capacity;
    h->arr = new data_type[h->capacity];
    if (h->arr == NULL)
    {
        cout << "\nMemory allocation failed";
        exit(0);
    }

    for (int i = 0; i < h->count; i++)
        h->arr[i] = temp[i];

    delete temp;

    //return h;
}

void DestroyHeap(Heap *h)
{
    if (h == NULL)
        return;
    delete h->arr;
    delete h;
}
///Returns the index of parent of the given index
int parentIndex(Heap *h, int i)
{
    int p = (i - 1) / 2;
    if (p < 0 || i > h->count)
        return -1;
    return p;
}

///Returns the index of the left child of the given index
int leftChildIndex(Heap *h, int i)
{
    int l = 2 * i + 1;
    if (l >= h->count || i < 0)
        return -1;

    return l;
}

///Returns the index of the right child of the given index
int rightChildIndex(Heap *h, int i)
{
    int r = 2 * i + 2;
    if (r >= h->count || i < 0)
        return -1;

    return r;
}

///Returns the value of the max element, i.e the root of the tree
int GetMax(Heap *h)
{
    if (h->count == 0)
        return -1;
    return h->arr[0];
}

///Checks the property of heap from the element at index i , and
// continue going up to parents untill that element has been set
// in its proper place
void PercolateUp_Recursive(Heap *h, int i)
{
    int p = parentIndex(h, i);
    if (p >= 0)
    {
        if (h->arr[i] > h->arr[p])
        {
            swap(&(h->arr[i]), &(h->arr[p]));
            PercolateUp_Recursive(h, p);
        }
    }
}

void PercolateUp_Iterative(Heap *h, int i)
{
    int p = parentIndex(h, i);

    while (p >= 0 && h->arr[i] > h->arr[p])
    {
        swap(&(h->arr[i]), &(h->arr[p]));
        i = p;
        p = parentIndex(h, i);
    }
}

///Similarly function to percolate down from the node at position i
void PercolateDown_Recursive(Heap *h, int i)
{
    int l = leftChildIndex(h, i);
    int r = rightChildIndex(h, i);

    int max_index = i;
    ///Find the max among that node and its 2 children
    if (l != -1)
        if (h->arr[l] > h->arr[max_index])
            max_index = l;

    if (r != -1)
        if (h->arr[r] > h->arr[max_index])
            max_index = r;

    ///If the max among those 3 is the current node, then heap's property is alright
    if (max_index == i)
        return;
    else //Swap the max child and the node and then conitue for that children
    {
        swap(&(h->arr[i]), &(h->arr[max_index]));
        PercolateDown_Recursive(h, max_index);
    }
}

void PercolateDown_Iterative(Heap *h, int i)
{
    int MaxChildIndex = leftChildIndex(h, i);
    int r, l;

    ///This loop will break when a node doesnt have any child
    while (MaxChildIndex != -1)
    {
        l = leftChildIndex(h, i);
        r = rightChildIndex(h, i);
        ///Find the max child between left and right
        if (r != -1)
            if (h->arr[r] > h->arr[l])
                MaxChildIndex = r;

        ///Compare the current node with its max child
        //and if heap's property is violated, then play with it
        if (h->arr[i] < h->arr[MaxChildIndex])
        {
            swap(&(h->arr[i]), &(h->arr[MaxChildIndex]));
            i = MaxChildIndex;
            MaxChildIndex = leftChildIndex(h, i);
        }
        else
            break;
    }
}

void Insert(Heap *h, int val)
{
    if (h->count == h->capacity)
        ResizeHeap(h);

    h->count++;
    h->arr[h->count - 1] = val; ///Insert the val int the last position

    ///Then if the property of heap is disturbed, then heapify it
    PercolateUp_Iterative(h, h->count - 1);
}

data_type DeleteMax(Heap *h)
{
    if (h->count == 0)
        return -1;

    ///Swap the root and the last node's value
    data_type val = h->arr[0];
    h->arr[0] = h->arr[h->count - 1];
    h->count--;

    ///Now check if any subtree from root has violated the property
    //of heap, if yeas, then fix it
    PercolateDown_Iterative(h, 0);

    ///Return the value of the previous root
    return val;
}

Heap *BuildHeap_byPercolateUp(int n, int *a)
{
    Heap *h = new Heap;
    if (h == NULL)
    {
        cout << "\nMemory allocation failed";
        exit(0);
    }
    h->capacity = n;
    h->arr = a;
    h->count = 0;

    for (int i = 0; i < n; i++)
        Insert(h, h->arr[i]);

    return h;
}

Heap *BuildHeap_byPercolateDown(int n, int *a)
{
    Heap *h = CreateHeap(n);
    h->count = n;
    ///Copy the whole array into the heap array
    for (int i = 0; i < n; i++)
        h->arr[i] = a[i];

    int lastInternal = parentIndex(h, n - 1); ///Last internal node is the parent of the last (leaf) node

    for (int i = lastInternal; i >= 0; i--)
        PercolateDown_Iterative(h, i);

    return h;
}

void HeapSort(int n, int *a)
{
    Heap *h = BuildHeap_byPercolateDown(n, a);
    int temp;

    for (int i = n - 1; i >= 0; i--)
    {
        temp = DeleteMax(h);
        a[i] = temp;
    }

    DestroyHeap(h);
}

void DisplayHeapArray(Heap *h)
{
    if (h->count == 0)
    {
        cout << "\nHeap is empty nigga\n";
        return;
    }
    for (int i = 0; i < h->count; i++)
        cout << h->arr[i] << " ";

    cout << "\n";
}

void DisplayArray(int n, int *a)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    cout << "\nHELLO NIGGA\n";

    /*int capacity = 10;
    Heap *h = CreateHeap(10);
    Insert(h, 10);
    Insert(h, 20);
    Insert(h, 30);
    Insert(h, 25);
    Insert(h, 5);
    Insert(h, 40);
    Insert(h, 35);

    //cout << "\nMax: " << GetMax(h) << endl;

    //cout << "\nh->count= " << h->count;
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    */
    /*cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    cout << "\nDeleted value: " << DeleteMax(h) << "\n";
    */
    //DisplayHeapArray(h);

    int n = 10;
    int a[n] = {3, 10, 2, 7, 5, 9, 6, 1, 4, 8};
    //Heap *h1 = BuildHeap_byPercolateDown(n, a);
    //DisplayHeapArray(h1);

    HeapSort(n, a);
    DisplayArray(n, a);

    return 0;
}