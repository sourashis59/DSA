

class DynamicArray {
    int *arr;
    int size;
    int capacity;

    static int INITIAL_CAPACITY;
    static int GROWTH_FACTOR;
    static int DELETION_FACTOR;
public:
    DynamicArray() {
        INITIAL_CAPACITY = 8;
        GROWTH_FACTOR = 2;
        DELETION_FACTOR = 4;
        
        size = 0;
        capacity = INITIAL_CAPACITY;
        arr = new int[capacity];
    }

    virtual ~DynamicArray() {
        delete []arr;
    }
    
    int size() {
        return size;
    }

    int capacity() {
        return capacity;
    }

    int front() {
        return arr[0];
    }

    int back() {
        return arr[size - 1];
    }

    void resize(int newCapacity) {
        int *copy = new int[newCapacity];
        for (int i = 0; i < size; ++i)
            copy[i] = arr[i];
        
        delete []arr;
        arr = copy;
        capacity = newCapacity;
    }

    void push_back(int val) {
        if (size == capacity) 
            resize(capacity * GROWTH_FACTOR);
        
        arr[size++] = val;
    }

    void pop_back() {
        --size;
        if (capacity > INITIAL_CAPACITY && size * DELETION_FACTOR <= capacity)
            resize((double)capacity * DELETION_FACTOR);
    }

};


class MyStack {
    DynamicArray arr;

public:
    MyStack() {
    }
}
