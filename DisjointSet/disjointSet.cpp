// Name: SOURASHIS MONDAL

#include <bits/stdc++.h>

using namespace std;

class DisjointSet
{
    int n;
    vector<int> parent;
    vector<int> treeSize;
    int componentCount;

public:
    DisjointSet(int n): n(n) {
        componentCount = n;
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
        x = findRoot(x), y = findRoot(y);
        if (x == y) return;
        //make x point to smaller tree root
        if (treeSize[x] > treeSize[y]) 
            swap(x, y);

        parent[x] = y;
        treeSize[y] += treeSize[x];
        --componentCount;
    }

    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }

    int getTreeSizeOfNode(int x) {
        return treeSize[findRoot(x)];
    }

    int getComponentCount() {
        return componentCount;
    }
};


int main()
{
    cout << "\n\nHello earth\n\n\n";

    return 0;
}
