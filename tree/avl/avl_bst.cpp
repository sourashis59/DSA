#include<bits/stdc++.h>
using namespace std;


class AVLTree {
    class Node {
    public:
        int key;
        int val;
        int height;
        int count; // no. of nodes in the subtree
        Node *left, *right;
        Node(int key = -1, int val = -1, Node *left = nullptr, Node *right = nullptr)
            : key(key), val(val), left(left), right(right) {
            count = 1; // for current node
            height = 1;
        }
    };

    private: Node *root;



    // ----------------------------------------- PUBLIC APIs ----------------------------------------------------//

    public: AVLTree() {
        root = nullptr;
    }

    public: int get(int key) {
        Node *x = root;
        while (x != nullptr) {
            if (key == x->key) return x->val;
            else if (key < x->key) x = x->left;
            else x = x->right;
        }
        // ASSUME: DEFAULT VALUE 0
        return 0;
    }
    
    public: void put(int key, int val) {
        root = put(root, key, val);
    }

    public: void remove(int key) {
        root = remove(root, key);
    }

    public: int size() {
        return size(root);
    }

    public: int height() {
        return height(root);
    }

    public: int minKey() {
        return minNode(root)->key;
    }

    public: int maxKey() {
        return maxNode(root)->key;
    }

    public: vector<int> keysInorder() {
        vector<int> res;
        keysInorder(root, res);
        return res;
    }

    // ceil(x) = smallest key in bst > x
    // returns null if not found
    public: int ceil(int x) {
        Node *u = root;
        Node *res = nullptr;
        while (root != nullptr) {
            if (x == u->key) return x;
            else if (x > u->key) u = u->right;
            else {
                res = u;
                u = u->left;
            }
        }
        return res == nullptr ? -1 : res->key;
    }

    // floor(x) = largest element in bst < x
    // returns null if not found
    public: int floor(int x) {
        Node *u = root;
        Node *res = nullptr;
        while (root != nullptr) {
            if (x == u->key) return x;
            else if (x < u->key) u = u->left;
            else {
                res = u;
                u = u->right;
            }
        }
        return res == nullptr ? -1 : res->key;
    }


    // rank(x) = no. of nodes < x
    public: int rank(int x) {
        return rank(root, x);
    }

    // select(k) = k-th node inorder
    public: int select(int k) {
        Node *res = select(root, k);
        return res == nullptr ? -1 : res->key;
    }











    // ---------------------------------------------- PRIVATE FUNCTIONS --------------------------------------------------------------------

    private: int size(Node *root) {
        if (root == nullptr) return 0;
        return root->count;
    }

    private: int height(Node *root) {
        if (root == nullptr) return 0;
        return root->height;
    }

    private: void updateHeightAndSize(Node *root) {
        root->height = 1 + max(height(root->left), height(root->right));
        root->count = 1 + size(root->left) + size(root->right);
    }

    private: int balanceFactor(Node *root) {
        if (root == nullptr) return 0;
        return height(root->left) - height(root->right);
    }


    private: int rank(Node* root, int x) {
        if (root == nullptr) return 0;
        if (x == root->key) return size(root->left);
        else if (x < root->key) return rank(root->left, x);
        // all nodes in roo.left subtree and root are < x
        else return size(root->left) + 1 + rank(root->right, x); 
    }

    // using inorder traversal we can find select() in O(N) time
    // by maintaining 'count', we can find select() in O(H) time
    private: Node* select(Node *root, int k) {
        // not found
        if (!root) return nullptr;
        // if number of smaller elements than root.key == k
        if (size(root->left) == k) return root;
        // if in left subtree
        else if (k < size(root->left)) return select(root->left, k);
        // if in right subtree
        // we know root and all nodes in root.left subtree are smaller 
        // than the target key 
        else return select(root->right, k - 1 - size(root->left));
    }


    private: void keysInorder(Node *root, vector<int> &res) {
        if (root == nullptr) return;
        keysInorder(root->left, res);
        res.push_back(root->key);
        keysInorder(root->right, res);
    }


    private: Node *minNode(Node *root) {
        if (root == nullptr) return nullptr;
        Node *x = root;
        while (x->left != nullptr) x = x->left;
        return x;
    }

    private: Node *maxNode(Node *root) {
        if (root == nullptr) return nullptr;
        Node *x = root;
        while (x->right != nullptr) x = x->right;
        return x;
    }


    // left rotates the node p and updates the 
    // height and size of the changed nodes 
    private: Node *leftRotate(Node *p) {
        Node *pr = p->right;
        p->right = pr->left;
        pr->left = p;
        updateHeightAndSize(p);
        updateHeightAndSize(pr);
        return pr;
    }

    // symmetrically opposite to leftRotate.
    // right rotates the node p and updates the 
    // height and size of the changed nodes 
    private: Node *rightRotate(Node *p) {
        Node *pl = p->left;
        p->left = pl->right;
        pl->right = p;
        updateHeightAndSize(p);
        updateHeightAndSize(pl);
        return pl;
    }

    // balances the tree rooted at 'root' 
    // [given both the subtress of root respects AVL property]
    // and also updates the height and count fields of the changed nodes
    private: Node *balance(Node *root) {
        int bf = balanceFactor(root);
        // left heavy
        if (bf == 2) {
            // left child is right heavy (LR case)
            if (balanceFactor(root->left) == -1)
                root->left = leftRotate(root->left);
            
            root = rightRotate(root);
        } 
        // right heavy [symmetrically opposite]
        else if (bf == -2) {
            // right child is left heavy (RL case)
            if (balanceFactor(root->right) == 1)
                root->right = rightRotate(root->right);
            
            root = leftRotate(root);
        }
        return root;
    }

    private: Node *put(Node *root, int key, int val) {
        if (root == nullptr) return new Node(key, val);
        if (root->key == key) root->val = val;
        else if (key < root->key) root->left = put(root->left, key, val);
        else root->right = put(root->right, key, val);
        
        // ------------------ NEW CODE FOR AVL [w.r.t normal BST] ---------------------//
        // update augmented informations
        updateHeightAndSize(root);
        // balance
        return balance(root);
    }


    private: Node *remove(Node *root, int key) {
        if (root == nullptr) return nullptr;
        if (key < root->key) root->left = remove(root->left, key);
        else if (key > root->key) root->right = remove(root->right, key);
        else {
            // case: 0 or 1 child
            if (root->left == nullptr) {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            if (root->right == nullptr) {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            // case: 2 children
            Node *successor = minNode(root->right);
            root->key = successor->key;
            root->val = successor->val; 
            root->right = remove(root->right, successor->key);
        }
        
        // ------------------ NEW CODE FOR AVL [w.r.t normal BST] ---------------------//
        // update augmented informations
        updateHeightAndSize(root);
        // balance
        return balance(root);
    }

};












bool isSorted(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1])
            return false;
    }
    return true;
}



// FOR TESTING
int main() {
    AVLTree bst;
    int n = 100000;
    for (int i = 0; i < n; ++i) {
        if (i % 1000 == 0) printf("\ni=%d, treeSize=%d, treeHeight=%d", i, bst.size(), bst.height());

        int r = rand() % 3;

        int val;
        if (r == 0) val = rand() % 10000;
        else if (r == 1) val = i;
        else val = n - i;
        
        // 30% times, delete a random node 
        // and 70% times insert
        r = rand() % 10;
        if (r == 0 || r == 1 || r == 2) {
            int treeSize = bst.size();
            int k = rand() % treeSize;
            int keyToDelete = bst.select(k); // k-th smallest element in bst
            bst.remove(keyToDelete);
        } else {
            bst.put(val, val);
        }

        if (bst.size() > 2 && bst.height() > 1.5 * log2(bst.size())) {
            int h = bst.height();
            int size = bst.size();
            throw new runtime_error("\nheight became more than 1.5 logN");
        }

        vector<int> inorder = bst.keysInorder();
        if (!isSorted(inorder)) {
            throw new runtime_error("\nNot sorted");
        }
    }

    while (bst.size()) {
        if (bst.size() % 1000 == 0) printf("\ntreeSize=%d, treeHeight=%d", bst.size(), bst.height());

        // delete random key
        int treeSize = bst.size();
        int k = rand() % treeSize;
        int keyToDelete = bst.select(k); // k-th smallest element in bst
        bst.remove(keyToDelete);


        // // delete terminal key
        // bst.remove(bst.maxKey());

        if (bst.size() > 2 && bst.height() > 1.5 * log2(bst.size())) {
            int h = bst.height();
            int size = bst.size();
            throw new runtime_error("\nheight became more than 1.5 logN");
        }
        
        vector<int> inorder = bst.keysInorder();
        if (!isSorted(inorder)) {
            throw new runtime_error("\nNot sorted");
        }
    }

    printf("\n\n\n---------------------------------------------------------Ok!---------------------------------------------------------\n\n\n");
}