class DynamicArray {
    int *_arr;
    int _size;
    int _capacity;

    static int INITIAL_CAPACITY;
    static double GROWTH_FACTOR;
    static double DELETION_FACTOR;
public:
    DynamicArray() {
        _size = 0;
        _capacity = INITIAL_CAPACITY;
        _arr = new int[_capacity];
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

    int front() {
        return _arr[0];
    }

    int back() {
        return _arr[_size - 1];
    }

    void resize(int newCapacity) {
        int *copy = new int[newCapacity];
        for (int i = 0; i < _size; ++i)
            copy[i] = _arr[i];
        
        delete []_arr;
        _arr = copy;
        _capacity = newCapacity;
    }

    void push_back(int val) {
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
int DynamicArray::INITIAL_CAPACITY = 8;
double DynamicArray::GROWTH_FACTOR = 1.5;
double DynamicArray::DELETION_FACTOR = 4;
        
