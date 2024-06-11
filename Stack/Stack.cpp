

template<typename T>
class Stack {
public:
    virtual ~Stack() {}
    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
    virtual T top() const = 0;
    virtual int size() const = 0;
    virtual bool empty() const = 0;
};




template <typename T>
class DynamicArrayStack: public Stack<T> {
    DynamicArray<T> arr;

public:
    DynamicArrayStack() {}
    int size() { return arr.size();}
    bool empty() { return arr.size() == 0; }
    void push(T val) {arr.push_back(val);}
    void pop() {arr.pop_back();}
    T top() {return arr.back();}
};





template <typename T>
class LinkedListStack: public Stack<T> {
    class Node {
    public:
        T val;
        Node *next;
        Node() {next = nullptr;}
        Node(const T& val, Node *next = nullptr): val(val), next(next) {}
    };
    
    Node *head;
    int _size;

public:
    LinkedListStack(): head(nullptr), _size(0) {}
    virtual ~LinkedListStack() {
        for (Node *p = head; p != nullptr; ) {
            Node *nextNode = p->next;
            delete p;
            p = nextNode;
        }
    }

    int size() {return _size;}
    bool empty() { return _size == 0; }
    
    void push(const T& val) {
        Node *newNode = new Node(val);
        ++_size;
        if (head == nullptr) head = newNode;
        else {
            newNode->next = head;
            head = newNode;
        }
    }
    
    void pop() {
        --_size;
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    T top() {return head->val;}
};
