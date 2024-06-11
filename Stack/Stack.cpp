

template <typename T>
class DynamicArray {
    T *_arr;
    int _size;
    int _capacity;

    static int INITIAL_CAPACITY;
    static double GROWTH_FACTOR;
    static double DELETION_FACTOR;
public:
    DynamicArray() {
        _size = 0;
        _capacity = INITIAL_CAPACITY;
        _arr = new T[_capacity];
    }

    ~DynamicArray() {
        delete []_arr;
    }
    
    int size() {
        return _size;
    }

    int capacity() {
        return _capacity;
    }

    T front() {
        return _arr[0];
    }

    T back() {
        return _arr[_size - 1];
    }

    void resize(int newCapacity) {
        T *copy = new T[newCapacity];
        for (int i = 0; i < _size; ++i)
            copy[i] = _arr[i];
        
        delete []_arr;
        _arr = copy;
        _capacity = newCapacity;
    }

    void push_back(T val) {
        if (_size == _capacity) 
            resize(_capacity * GROWTH_FACTOR);
        
        _arr[_size++] = val;
    }

    void pop_back() {
        --_size;
        if (_capacity > INITIAL_CAPACITY && _size * DELETION_FACTOR <= _capacity)
            resize((double)_capacity / DELETION_FACTOR);
    }

};
// Define and initialize static member variables outside the class
template <typename T>
int DynamicArray<T>::INITIAL_CAPACITY = 8;

template <typename T>
double DynamicArray<T>::GROWTH_FACTOR = 1.5;

template <typename T>
double DynamicArray<T>::DELETION_FACTOR = 4;
        











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
        ++_size;
        Node *oldHead = head;
        head = new Node(val, oldHead);
    }
    
    void pop() {
        --_size;
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    T top() {return head->val;}
};
