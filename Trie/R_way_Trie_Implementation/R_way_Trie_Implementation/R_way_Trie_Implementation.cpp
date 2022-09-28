#include<iostream>
#include<string>
#include<vector>
using namespace std;



class TrieNode
{
	
public:

	int val;
	bool hasVal;
	TrieNode** children;

	static int R;
	static int NO_VALUE;

	TrieNode(int val = TrieNode::NO_VALUE)
	{
		this->val = val;
		this->hasVal = false;
		this->children = new TrieNode * [R];
		
		for (int i = 0; i < TrieNode::R; i++)
			this->children[i] = NULL;
	}

	static int getCharInd(char c)
	{
		return c - 'a';
	}

	static int getCharFromInd(int ind)
	{
		return 'a' + ind;
	}
};
int TrieNode::R = 26;
int TrieNode::NO_VALUE= -1;

class TrieSymbolTable
{
	TrieNode* root;
	int trieSize;


protected:
	
	
	TrieNode* putHelper1(TrieNode* root, int d, const string &key, int val)
	{
		if (!root)
			root = new TrieNode();

		if (d == key.size())
		{
			root->val = val;
			root->hasVal = true;
			return root;
		}

		int c = TrieNode::getCharInd(key[d]);
		root->children[c] = putHelper1(root->children[c], d + 1, key, val);
		return root;
	}

	TrieNode* putHelper2(TrieNode* root, int currInd , int endInd, const string& key, int val)
	{
		if (!root)
			root = new TrieNode();

		if (currInd == endInd + 1)
		{
			root->val = val;			
			root->hasVal = true;
			return root;
		}

		int c = TrieNode::getCharInd(key[currInd]);
		root->children[c] = putHelper2(root->children[c], currInd + 1, endInd, key, val);
		return root;
	}

	TrieNode* getHelper1(TrieNode* root, int d, const string& key)
	{
		if (!root)
			return NULL;

		if (d == key.size())
			return root;
		
		int c = TrieNode::getCharInd(key[d]);

		return getHelper1(root->children[c], d + 1, key);
	}
	
	TrieNode* getHelper2(TrieNode* root, int currInd, int endInd, const string& key)
	{
		if (!root)
			return NULL;

		if (currInd == endInd + 1)
			return root;

		int c = TrieNode::getCharInd(key[currInd]);

		return getHelper2(root->children[c], currInd + 1,  endInd, key);
	}

	void inorderCollect(TrieNode* root, string& prefix, vector<string>& q)
	{
		if (!root)
			return;

		if (root->hasVal)
			q.push_back(prefix);

		for (int i = 0; i < TrieNode::R; i++)
		{
			char c = TrieNode::getCharFromInd(i);
			
			prefix.push_back(c);
			inorderCollect(root->children[i], prefix, q);
			prefix.pop_back();
		}
	}

public: 
	TrieSymbolTable()
	{
		this->root = new TrieNode();
		this->trieSize = 0;
	}

	//inserts (key, val) in the trie
	void put(const string& key, int val)
	{

		//if the key was not present previously , then increment size
		if (this->get(key) == TrieNode::NO_VALUE)
			this->trieSize++;

		root = putHelper1(root, 0, key, val);
	}
	
	//inserts (key[startInd...endInd], val) in  trie
	void put(int startInd, int endInd, const string& key, int val)
	{
		
		//if the key was not present previously , then increment size
		if (this->get(startInd, endInd, key) == TrieNode::NO_VALUE)
			this->trieSize++;

		root = putHelper2(root, startInd, endInd, key, val);
	}


	int get(const string& key)
	{
		TrieNode* x = getHelper1(root, 0, key);
		return x ? x->val : TrieNode::NO_VALUE;
	}



	//gets value of key[startInd...endInd] 
	int get(int startInd, int endInd, const string& key)
	{
		TrieNode* x = getHelper2(root, startInd, endInd, key);
		return x ? x->val : TrieNode::NO_VALUE;
	}

	int size()
	{
		return this->trieSize;
	}


	vector<string> getAllKeys()
	{
		vector<string> q;
		string prefix = "";
		inorderCollect(root, prefix, q);

		return q;
	}

	vector<string> getKeysWithPrefix(const string &prefix)
	{
		vector<string> q;
		string key = prefix;

		TrieNode* x = getHelper1(root, 0, key);
		inorderCollect(x, key, q);

		return q;


	}


	//lastInd = lastInd of ancestor which has more than one child
	//currInd = current indes of the node from root
	void populateShortestUniquePrefixLengthForAllKeysHelper(TrieNode* root, int currInd, int lastInd)
	{
		if (!root)
			return;

		if (root->hasVal)
			root->val = lastInd + 1;

		int childCount = 0;
		for (int i = 0; i < TrieNode::R; i++)
		{
			if (root->children[i])
				childCount++;
		}

		if (childCount > 1)
			lastInd = currInd;

		for (int i = 0; i < TrieNode::R; i++)
			populateShortestUniquePrefixLengthForAllKeysHelper(root->children[i], currInd + 1, lastInd);
	}
	void populateShortestUniquePrefixLengthForAllKeys()
	{
		populateShortestUniquePrefixLengthForAllKeysHelper(root, 0, 0);
	}
};



int main()
{

	cout << "\n\nHello world\n\n\n";
	//vector<string> arr = { "sourashis", "white", "negus", "king", "abbababa", "helloworld", "noobda"};
	vector<string> arr = { "zebra", "dog", "duck" ,"dove" };

	TrieSymbolTable t;
	for (auto& str : arr)
	{
		t.put(str, 0);
	}


	vector<string> keys = t.getAllKeys();
	cout << "\n\nall keys :\n";
	for (string& str : keys)
		cout << str <<endl;


	cout << "\n\n\nEND ______________________________________________________\n\n\n";

}

