
#include<bits/stdc++.h>
using namespace std;

class Trie {
    class TrieNode {
        static int R; 
    public:
        int val;
        int trie_size;
        vector<TrieNode*> children;

        TrieNode(int val = 0): val(val), trie_size(0), children(vector<TrieNode*>(26, nullptr)) {}
        TrieNode*& get_child(char ch) { return children[ch - 'a']; }
    };
    int R = 26; 


private:
    static int NO_VALUE;
    TrieNode* _root;

    TrieNode *get(TrieNode *root, int ind, const string &key) {
        if (!root || ind == key.size()) return root;
        return get(root->get_child(key[ind]), ind + 1, key);
    }

    TrieNode *put(TrieNode *root, int ind, const string &key, int val) {
        if (!root) root = new TrieNode(NO_VALUE);
        if (ind == key.size()) { root->val = val; root->trie_size = 1; return root; }
        root->children[key[ind] - 'a'] = put(root->get_child(key[ind]), ind + 1, key, val);
        ++root->trie_size;
        return root;
    }
    
    void destroy(TrieNode *root) {
        if (!root) return;
        for (TrieNode* child: root->children) 
            destroy(child);
        
        delete root;
    }

    static int size(TrieNode *root) { return root == nullptr ? 0 : root->trie_size; }

    int rank(TrieNode *root, int ind, const string &key) {
        if (ind == key.size()) return 0;
        int res = 0;
        if (root->val == 1) ++res;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (key[ind] == ch) {
                res += rank(root->get_child(ch), ind + 1, key);
                break;
            }
            res += size(root->get_child(ch));
        }
        return res;
    }

    string find(TrieNode *root, int rank) {
        if (!root || (rank == 0 && root->val == 1)) return "";
        if (root->val == 1) --rank;
        int element_count = 0;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (rank < element_count + size(root->get_child(ch))) {
                return ch + find(root->get_child(ch), rank - element_count);
            }
            element_count += size(root->get_child(ch));
        }     
        return "";
    }

public:
    Trie(): _root(new TrieNode(NO_VALUE)) {}
    ~Trie() { destroy(_root); _root = nullptr; }

    void put(const string &key) { 
        if (get(_root, 0, key) != nullptr) return;
        _root = put(_root, 0, key, 1); 
    }

    //* returns rank(index in sorted order) of given key 
    int rank(const string &key) { return rank(_root, 0, key); }

    //* returns {rank}-th key
    string find(int rank) {
        if (size(_root) <= rank) return "";
        return find(_root, rank);
    }

    //* returns {rank}-th key present with given {starting_char}
    string find(char starting_char, int rank) {
        if (size(_root->get_child(starting_char)) <= rank) return "";
        return starting_char + find(_root->get_child(starting_char), rank);
    }
};

int Trie::NO_VALUE = 0;



