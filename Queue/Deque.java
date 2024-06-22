import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
    private Item []arr;
    private int capacity;

    //ind of first element
    private int first;
    //ind after the last element
    private int last;

    //you must keep size field explicitly, you cant compute size = last - first) % capacity
    //because, if first == last, you can not tell if the size == 0 or size == capacity
    private int _size;



    private int posMod(int x, int m) {
        x = x % m;
        if (x < 0) x += m;
        return x;
    }

    private void resize(int newCapacity) {
        Item []copy = (Item [])new Object[newCapacity];
        for (int i = 0; i < _size; ++i) {
            copy[i] = arr[(first + i) % capacity];
        }
        capacity = newCapacity;
        arr = copy;
        first = 0;
        last = _size;
    }

    // construct an empty deque
    public Deque() {
        capacity = 2;
        arr = (Item[])new Object[capacity]; //default initial capacity = 8
        first = last = _size = 0;
    }

    // is the deque empty?
    public boolean isEmpty() {
        return _size == 0;
    }

    // return the number of items on the deque
    public int size() {
        return _size;
    }

    // add the item to the front
    public void addFirst(Item item) {
        if (item == null) throw new IllegalArgumentException("item should not be null in addFirst()");
        if (size() == capacity) resize((int)(capacity * 2));
        first = posMod(first - 1, capacity);
        arr[first] = item;
        ++_size;
    }

    // add the item to the back
    public void addLast(Item item) {
        if (item == null) throw new IllegalArgumentException("item should not be null in addLast()");
        if (size() == capacity) resize((int)(capacity * 2));
        arr[last] = item;
        last = (last + 1) % capacity;
        ++_size;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        if (size() == 0) throw new NoSuchElementException("queue is empty!");
        Item item = arr[first];
        arr[first] = null; //to prevent loitering
        first = (first + 1) % capacity;
        --_size;
        if (_size > 0 && _size == capacity / 4) resize(capacity / 2);
        return item;
    }

    // remove and return the item from the back
    public Item removeLast() {
        if (size() == 0) throw new NoSuchElementException("queue is empty!");
        last = posMod(last - 1, capacity);
        Item item = arr[last];
        arr[last] = null; //to prevent loitering
        --_size;
        if (_size > 0 && _size == capacity / 4) resize(capacity / 2);
        return item;
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new DequeIterator();
    }

    // Inner class implementing the Iterator interface
    private class DequeIterator implements Iterator<Item> {
        private int index = 0;

        // Implementing the Iterator interface methods
        @Override
        public boolean hasNext() {
            return index < _size;
        }

        @Override
        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException("No more elements in the collection");
            }
            Item item = arr[(first + index) % capacity];
            ++index;
            return item;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException("Remove operation is not supported");
        }
    }

    // unit testing (required)
    public static void main(String[] args) {
        Deque<Integer> q = new Deque<>();
        for (int i = 0; i < 30; ++i) q.addLast(i);
        for (int i = 2; i < 5; ++i) q.addFirst(i);
        System.out.println("\nQueue: size=" + q.size() + ", : ");
        for (int x: q) System.out.print(x + ", ");
        while (!q.isEmpty()) {
            System.out.println("first: " + q.removeFirst());
        }
        for (int i = 0; i < 30; ++i) q.addLast(i);
        while (!q.isEmpty()) {
            System.out.println("last: " + q.removeLast());
        }

//        Deque<Integer> deque = new Deque<>();
//        deque.addFirst(1);
//        deque.addFirst(2);
//        deque.addFirst(3);
//        deque.removeLast();

    }

}

