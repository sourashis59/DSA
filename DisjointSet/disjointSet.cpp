// Name: SOURASHIS MONDAL

#include <bits/stdc++.h>

using namespace std;

class DisjointSet
{
    int *parent;
    int *treeSize;
    int n;

public:
    DisjointSet(int n)
    {
        this->n = n;
        parent = new int[n];
        treeSize = new int[n];

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            treeSize[i] = 1;
        }
    }

    //*returns root of the tree containing x (returns the identifier of the set containing x)
    //*Path compression: make the root of the tree parent of all nodes in the path from root to x

    int findSet(int x)
    {
        // doesnt exist
        if (x < 0 || x >= this->n)
            return -1;

        if (x == parent[x])
            return x;

        int root = findSet(parent[x]);

        //*for path compression: make the root of the tree parent of x
        parent[x] = root;

        return root;
    }

    void unionSets(int x, int y)
    {
        int root1 = findSet(x);
        int root2 = findSet(y);

        if (root1 == root2)
            return;

        if (this->treeSize[root1] <= this->treeSize[root2])
        {
            parent[root1] = root2;
            this->treeSize[root2] += this->treeSize[root1];
        }
        else
        {
            parent[root2] = root1;
            this->treeSize[root1] += this->treeSize[root2];
        }
    }
};

int main()
{
    cout << "\n\nHello earth\n\n\n";

    return 0;
}