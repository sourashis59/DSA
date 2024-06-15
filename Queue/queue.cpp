template<typename T>
class Queue {
public:
    virtual ~Queue() {}
    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
    virtual T front() = 0;
    virtual int size() = 0;
    virtual bool empty() = 0;
};


template<typename T>
class CircularArrayQueue: public Queue<T> {
    T *arr;
    int capacity;

    //ind of first element
    int first;
    //ind after the last element
    int last;

    //you must keep size field explicitly, you cant compute size = last - first) % capacity
    //because, if first == last, you can not tell if the size == 0 or size == capacity
    int _size;


    int posMode(int x, int m) {
        x = x % m;
        if (x < 0) x += m;
        return x;
    }

    void resize(int newCapacity) {
        T *copy = new T[newCapacity];
        for (int i = 0; i < _size; ++i) {
            copy[i] = arr[(first + i) % capacity]; 
        }
        capacity = newCapacity;
        delete []arr;
        arr = copy;
        first = 0;
        last = _size;
    }

public:
    CircularArrayQueue() {
        arr = new T[8]; //default initial capacity = 8
        capacity = 8;
        first = last = _size = 0;
    }

    virtual ~CircularArrayQueue() {
        delete []arr;
    }

    int size() {
        return _size;
    }

    bool empty() {
        return size() == 0;
    }

    T front() {
        return arr[first];
    }

    void push(const T &value) {
        if (size() == capacity) resize(capacity * 2);
        arr[last] = value;
        last = (last + 1) % capacity;
        ++_size;
    }

    void pop() {
        first = (first + 1) % capacity;
        --_size;
        if (_size > 0 && capacity > 8 && _size == capacity / 4) resize(capacity / 2);
    }

};
