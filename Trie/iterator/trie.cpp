// Question: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/


class TrieNode
{
public:

    int val;
    bool hasVal;
    TrieNode** children;

    static int R;
    static int NO_VALUE;

    TrieNode(int val = TrieNode::NO_VALUE) {
        this->val = val;
        this->hasVal = false;
        this->children = new TrieNode * [R];
        
        for (int i = 0; i < TrieNode::R; i++)
            this->children[i] = NULL;
    }

    ~TrieNode() {
        // First delete each child recursively
        for (int i = 0; i < TrieNode::R; ++i) {
            delete children[i];
        }
        // Then delete the array of children
        delete[] children;
    }

    TrieNode *getChild(char ch) {
        return children[getCharInd(ch)];
    }

    static int getCharInd(char c) {
        return c - 'a';
    }

    static int getCharFromInd(int ind) {
        return 'a' + ind;
    }
};

int TrieNode::R = 26;
int TrieNode::NO_VALUE = -1;

class TrieSymbolTable
{
    TrieNode* root;
    int trieSize;

protected:
    
    TrieNode* putHelper1(TrieNode* root, int d, const string &key, int val) {
        if (!root)
            root = new TrieNode();

        if (d == key.size()) {
            root->val = val;
            root->hasVal = true;
            return root;
        }

        int c = TrieNode::getCharInd(key[d]);
        root->children[c] = putHelper1(root->children[c], d + 1, key, val);
        return root;
    }

    TrieNode* getHelper1(TrieNode* root, int d, const string& key) {
        if (!root)
            return NULL;

        if (d == key.size())
            return root;
        
        int c = TrieNode::getCharInd(key[d]);

        return getHelper1(root->children[c], d + 1, key);
    }
    
    void destroy(TrieNode* root) {
        if (!root) return;
        for (int i = 0; i < TrieNode::R; ++i) {
            destroy(root->children[i]);
        }
        delete root;
    }

public: 
    TrieSymbolTable() {
        this->root = new TrieNode();
        this->trieSize = 0;
    }

    ~TrieSymbolTable() {
        destroy(root);
        root = nullptr;
    }

    void reset() {
        destroy(root);
        root = new TrieNode();
        trieSize = 0;
    }
    
    //inserts (key, val) in the trie
	void put(const string& key, int val)
	{

		//if the key was not present previously , then increment size
		if (this->get(key) == TrieNode::NO_VALUE)
			this->trieSize++;

		root = putHelper1(root, 0, key, val);
	}
	
	

	int get(const string& key)
	{
		TrieNode* x = getHelper1(root, 0, key);
		return x ? x->val : TrieNode::NO_VALUE;
	}


	int size()
	{
		return this->trieSize;
	}



    class Iterator {
        TrieNode *root;
        TrieNode *currNode;
    
    public:
        Iterator(TrieNode *root) {
            currNode = root;
            this->root = root;
        }

        bool move(char ch) {
            if (!currNode || !currNode->getChild(ch)) return false;
            currNode = currNode->getChild(ch);
            return true; 
        }
    };


    Iterator getIterator() {
        return Iterator(root);
    }
};




class Solution {
public:

    TrieSymbolTable *trie;
    string target;
    int maxWordLen;

    vector<int> memo;

    int mc(int i) {
        if (i == target.size()) return 0;
        if (memo[i] != INT_MAX) return memo[i];

        int res = INT_MAX;
        auto itr = trie->getIterator();
        for (int j = i; j < i + maxWordLen && j < target.size(); ++j) {
            if (!itr.move(target[j]))
                break;
            
            int m1 = mc(j + 1);
            if (m1 != -1) res = min(res, 1 + m1);
        }
        if (res == INT_MAX) res = -1;
        return memo[i] = res;
    }

    int minValidStrings(vector<string>& words, string target) {
        maxWordLen = 0;
        if (trie) {
            delete trie;
            trie = nullptr;
        }
        trie = new TrieSymbolTable();    
        for (const string &word: words) {
            trie->put(word, 1);
            maxWordLen = max(maxWordLen, (int)word.size());
        }
        this->target = target;  
        

        memo = vector<int>(target.size(), INT_MAX);
        return mc(0);
    }
};
