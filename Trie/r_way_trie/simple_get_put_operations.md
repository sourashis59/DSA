```cpp
class Trie {
        
    class TrieNode {
        static int R;

        int _val;
        bool _has_val;
        vector<TrieNode*> _children;
    public:
        TrieNode(int val): _val(val), _has_val(false), _children(vector<TrieNode*>(26, nullptr)) {}
        
        int get_val() { return _val; }
        void set_val(int val) { _val = val, _has_val = true; }
        bool has_val() { return _has_val; }
        vector<TrieNode*>& get_children() { return _children; }
        TrieNode*& get_child(char ch) { return _children[ch - 'a']; }
        void set_child(char ch, TrieNode *val) { _children[ch - 'a'] = val; }
    };
    int R = 26; 



    static int NO_VALUE;
    TrieNode* _root;



    // TrieNode *get_iterative(const string &key) {
    //     TrieNode *p = _root;
    //     for (char ch: key) {
    //         if (!p) return nullptr;
    //         p = p->get_child(ch);
    //     }
    //     return p;
    // }

    TrieNode *get(TrieNode *root, int ind, const string &key) {
        if (!root || ind == key.size()) return root;
        return get(root->get_child(key[ind]), ind + 1, key);
    }

    TrieNode *put(TrieNode *root, int ind, const string &key, int val) {
        if (!root) root = new TrieNode(NO_VALUE);
        if (ind == key.size()) { root->set_val(val); return root; }
        root->set_child(key[ind], put(root->get_child(key[ind]), ind + 1, key, val));
        return root;
    }
    
    void destroy(TrieNode *root) {
        if (!root) return;
        for (TrieNode* child: root->get_children()) 
            destroy(child);
        
        delete root;
    }

public:
    Trie(): _root(new TrieNode(NO_VALUE)) {}
    ~Trie() { destroy(_root); _root = nullptr; }

    int get(const string &key) {
        TrieNode *node = get(_root, 0, key);
        return (node == nullptr || !node->has_val()) ? NO_VALUE : node->get_val();
    }

    void put(const string &key, int val) { _root = put(_root, 0, key, val); }
};

int Trie::NO_VALUE = 0;

```