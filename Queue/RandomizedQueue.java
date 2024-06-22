import edu.princeton.cs.algs4.StdRandom;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private Item []arr;
    private int _size;

    private void resize(int newCapacity) {
        Item []copy = (Item[])new Object[newCapacity];
        for (int i = 0; i < _size; ++i) {
            copy[i] = arr[i];
        }
        arr = copy;
    }

    private void swap(Object []arr, int ind1, int ind2) {
        Object temp = arr[ind1];
        arr[ind1] = arr[ind2];
        arr[ind2] = temp;
    }

    // construct an empty randomized queue
    public RandomizedQueue() {
        arr = (Item[])new Object[2]; //default initial capacity = 8
        _size = 0;
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return _size == 0;
    }

    // return the number of items on the randomized queue
    public int size() {
        return _size;
    }

    // add the item
    public void enqueue(Item item) {
        if (item == null) throw new IllegalArgumentException("item should not be null in addLast()");
        if (size() == arr.length) resize(arr.length * 2);
        arr[_size++] = item;
    }

    // remove and return a random item
    public Item dequeue() {
        if (size() == 0) throw new NoSuchElementException("queue is empty!");
        //random integer in range [0, size)
        int r = StdRandom.uniformInt(size());
        //swap the r-th element with last and return last element
        swap(arr, r, _size - 1);

        //same code as stack
        Item item = arr[_size - 1];
        arr[_size - 1] = null; //to prevent loitering
        --_size;
        if (_size > 0 && arr.length > 2 && _size == arr.length / 4) resize(arr.length / 2);
        return item;
    }

    // return a random item (but do not remove it)
    public Item sample() {
        if (size() == 0) throw new NoSuchElementException("queue is empty!");
        //random integer in range [0, size)
        int r = StdRandom.uniformInt(size());
        return arr[r];
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator(size());
    }


    // Inner class implementing the Iterator interface
    private class RandomizedQueueIterator implements Iterator<Item> {
        private int curr; //current ind in randomlyOrderedInd[] array
        private int []randomlyOrderedInd;

        public RandomizedQueueIterator(int size) {
            curr = 0;
            randomlyOrderedInd = new int[size];
            for (int i = 0; i < size; ++i) randomlyOrderedInd[i] = i;
            StdRandom.shuffle(randomlyOrderedInd);
        }

        // Implementing the Iterator interface methods
        @Override
        public boolean hasNext() {
            return curr < randomlyOrderedInd.length;
        }

        @Override
        public Item next() {
            if (!hasNext()) throw new NoSuchElementException("No more elements in the collection");
            return arr[randomlyOrderedInd[curr++]];
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException("Remove operation is not supported");
        }
    }




    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<Integer> q = new RandomizedQueue<>();
        for (int i = 0; i < 10; ++i) q.enqueue(i);
        System.out.println("\nQueue: size=" + q.size() + ", : ");
        for (int x: q) System.out.print(x + ", ");
        System.out.println("\nQueue: size=" + q.size() + ", : ");
        for (int x: q) System.out.print(x + ", ");
        System.out.println("\nQueue: size=" + q.size() + ", : ");
        for (int x: q) System.out.print(x + ", ");
        System.out.println();
        while (!q.isEmpty()) {
            System.out.println("dequeued item: " + q.dequeue());
        }
    }

}
