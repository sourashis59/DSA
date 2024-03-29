// Name: SOURASHIS MONDAL

#include <bits/stdc++.h>

using namespace std;

class DisjointSet
{
    int n;
    vector<int> parent;
    vector<int> treeSize;

public:
    DisjointSet(int n): n(n) {
        treeSize = vector<int>(n, 1);
        parent = vector<int>(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    //*recursive: find(x) = makes ancestors of x point to root, and returns root
    //*Path compression: make the root of the tree parent of all nodes in the path from root to x
    int findRoot(int x) {
        if (x != parent[x]) parent[x] = findRoot(parent[x]);
        return parent[x];
    }

    //iterative
    int findRootIterative(int x) {
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

    int getTreeSizeOfNode(int x) {
        return treeSize[findRoot(x)];
    }
};


int main()
{
    cout << "\n\nHello earth\n\n\n";

    return 0;
}