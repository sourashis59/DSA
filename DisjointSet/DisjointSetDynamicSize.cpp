// Name: SOURASHIS MONDAL

#include <bits/stdc++.h>

using namespace std;

class DisjointSetDynamicSize
{
    unordered_map<int, int> parent;
    unordered_map<int, int> treeSize;

public:
    DisjointSetDynamicSize() {}

    //*inserts a tree with single element x, into the 
    //*disjoint set forest
    void insertTree(int x) {
        treeSize[x] = 1;
        parent[x] = x;
    }

    //*recursive: find(x) = makes ancestors of x point to root, and returns root
    //*Path compression: make the root of the tree parent of all nodes in the path from root to x
    int findRoot(int x) {
        //*if parent does not exist, insert a tree with one element x, into the DisjoinSet forest
        if (parent.count(x) == 0) insertTree(x);
        if (x != parent[x]) parent[x] = findRoot(parent[x]);
        return parent[x];
    }

    //iterative
    int findRootIterative(int x) {
        //*if parent does not exist, insert a tree with one element x, into the DisjoinSet forest
        if (parent.count(x) == 0) insertTree(x);
        while(x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void doUnion(int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);
        if (rootX == rootY)
            return;

        //make rootX point to smaller tree root
        if (treeSize[rootX] > treeSize[rootY]) 
            swap(rootX, rootY);

        parent[rootX] = rootY;
        treeSize[rootY] += treeSize[rootX];
    }

    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }
};


int main()
{
    cout << "\n\nHello earth\n\n\n";

    return 0;
}