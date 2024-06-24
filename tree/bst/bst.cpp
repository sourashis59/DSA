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

    private: Node *root;

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

    // ceil(x) = smallest key in bst > x
    // returns null if not found
    public: int ceil(int x) {
        Node *u = root;
        Node *res = nullptr;
        while (root != nullptr) {
            if (key == u->key) return key;
            else if (key > u->key) u = u->right;
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
        Node u = root;
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











    // ------------------------------------------------------------------------------------------------------------------
    private: int rank(Node* root, int x) {
        if (root == nullptr) return 0;
        if (x == root->key) return size(root->left);
        else if (x < root->key) return rank(root->left, x);
        // all nodes in roo.left subtree and root are < x
        else return size(root->left) + 1 + rank(root->right, x); 
    }

    // using inorder traversal we can find select() in O(N) time
    // by maintaining 'count', we can find select() in O(H) time
    private: Node* select(Node root, int k) {
        // not found
        if (!root) return nullptr;
        // if number of smaller elements than root.key == k
        if (size(root->left) == k) return root->key;
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
