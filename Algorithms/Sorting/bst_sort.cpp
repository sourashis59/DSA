// this is not Height balanced, it's just BST
class BST {
    class Node {
    public:
        int key;
        int val;
        int count; // no. of nodes in the subtree
        Node *left, *right;
        Node(int key = -1, int val = -1, Node *left = nullptr, Node *right = nullptr):
            key(key), val(val), left(left), right(right) {
                count = 1; // for current node
        }
    };

    Node *root;

    public: BST() {
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

    public: int minKey() {
        return min(root)->key;
    }

    public: vector<int> keysInorder() {
        vector<int> res;
        keysInorder(root, res);
        return res;
    }

    private: void keysInorder(Node *root, vector<int> &res) {
        if (root == nullptr) return;
        keysInorder(root->left, res);
        res.push_back(root->key);
        keysInorder(root->right, res);
    }


    private: int size(Node *root) {
        if (root == nullptr) return 0;
        return root->count;
    }

    private: Node *put(Node *root, int key, int val) {
        if (root == nullptr) return new Node(key, val);
        if (root->key == key) root->val = val;
        else if (key < root->key) root->left = put(root->left, key, val);
        else root->right = put(root->right, key, val);
        
        // update count
        root->count = 1 + size(root->left) + size(root->right);
        return root;
    }

    private: Node *min(Node *root) {
        if (root == nullptr) return nullptr;
        Node *x = root;
        while (x->left != nullptr) x = x->left;
        return x;
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
            Node *successor = min(root->right);
            root->key = successor->key;
            root->val = successor->val; 
            root->right = remove(root->right, successor->key);
        }
        // update count
        root->count = 1 + size(root->left) + size(root->right);
        return root;
    }

};

class Sorter {
public: 

    void shuffle(vector<int> &a) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            int r = rand() % (i + 1);
            swap(a[i], a[r]);
        }
    }

    // average case time complexity: O(N * logN) 
    // [because of random ordering of insertion into BST]
    vector<int> sortArray(vector<int>& a) {
        int n = a.size();
        BST bst;

        // shuffle is important for performance
        // if you add keys in bst in random order,
        // then height remains ~ N * logN
        shuffle(a);
        
        for (int x: a) {
            int freq = bst.get(x);
            bst.put(x, freq + 1);
        }

        int k = 0;
        for (int key: bst.keysInorder()) {
            int freq = bst.get(key);
            for (int i = 0; i < freq; ++i) 
                a[k++] = key;
        }

        //// ----------------- FOR TESTING --------------------
        // int k = 0;
        // while (bst.size()) {
        //     int minKey = bst.minKey();
        //     int freq = bst.get(minKey);
        //     bst.remove(minKey);
        //     for (int i = 0; i < freq; ++i) 
        //         a[k++] = minKey;
        // }

        return a;    
    }
};
