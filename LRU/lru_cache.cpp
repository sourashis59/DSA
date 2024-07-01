class LRUCache {
    class Node {
    public:
        int key;
        int val;
        Node *next, *prev;
        Node(int key = -1, int val = -1): key(key), val(val), next(nullptr), prev(nullptr) {}
    };

    class LinkedList {
    private:    
        Node *head, *tail;
    
        public: LinkedList() {
            head = new Node();
            tail = new Node();
            head->next = tail;
            tail->prev = head;
        }

        // removes last node and returns the key 
        public: int removeLastNode() {
            if (head->next == tail) return -1;
            Node *temp = tail->prev;
            removeNode(temp);
            int key = temp->key;
            delete temp;
            return key;
        }

        // removes the given node from linked list, but does not deallocate the node
        public: void removeNode(Node *x) {
            x->next->prev = x->prev;
            x->prev->next = x->next;
        }

        // inserts the given node to front of linked list
        public: void insertFront(Node *x) {
            x->next = head->next;
            head->next->prev = x;
            head->next = x;
            x->prev = head;
        }

    };


    int capacity;
    unordered_map<int, Node*> keyAddress; // keyAddress[key] = pointer to the node containing key
    LinkedList ll;
public:
    LRUCache(int capacity): capacity(capacity) {
    }
    
    int get(int key) {
        if (keyAddress.count(key) == 0) return -1;
        Node *node = keyAddress[key];
        ll.removeNode(node);
        ll.insertFront(node);
        return node->val;
    }
    
    void put(int key, int value) {
        // if key already present, just update value
        if (keyAddress.count(key)) {
            int temp = get(key); // to bring the node to front
            keyAddress[key]->val = value; // update value
            return;
        }

        if (size() == capacity) {
            int removedKey = ll.removeLastNode();
            keyAddress.erase(removedKey);
        }

        keyAddress[key] = new Node(key, value);
        ll.insertFront(keyAddress[key]);
    }

    int size() {
        return keyAddress.size();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
