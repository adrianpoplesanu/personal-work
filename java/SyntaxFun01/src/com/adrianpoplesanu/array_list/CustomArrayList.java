package com.adrianpoplesanu.array_list;

import java.util.Arrays;

public class CustomArrayList<T> implements CustomArrayListInterface<T> {
    private int capacity = 4;
    private T[] elements;
    int size = 0;

    public CustomArrayList() {
        elements = (T[]) new Object[capacity];
    }

    public CustomArrayList(int capacity) {
        this.capacity = capacity;
        elements = (T[]) new Object[capacity];
    }

    public CustomArrayList(CustomArrayList<T> oldArray) {
        this.capacity = oldArray.capacity;
        elements = Arrays.copyOf(oldArray.elements, oldArray.size());
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public T get(int index) {
        checkRange(index);
        return elements[index];
    }

    @Override
    public void set(int index, T element) {
        checkRange(index);
        elements[index] = element;
    }

    @Override
    public void add(T element) {
        if (size >= capacity) {
            growSize();
        }
        elements[size++] = element;
    }

    @Override
    public T remove(int index) {
        checkRange(index);
        T element = elements[index];
        for (int i = index; i < size() - 1; i++) {
            elements[i] = elements[i + 1];
        }
        size--;
        if (size < capacity / 4) {
            if (capacity >> 1 >= 4) {
                shrinkSize();
            }
        }
        return element;
    }

    private void checkRange(int index) {
        if (index >= size() || index < 0) {
            throw new IndexOutOfBoundsException();
        }
    }

    private void growSize() {
        T[] oldArray = elements;
        capacity = capacity << 1;
        elements = (T[]) new Object[capacity];
        for (int i = 0 ; i < oldArray.length; i++) elements[i] = oldArray[i];
    }

    private void shrinkSize() {
        T[] oldArray = elements;
        capacity = capacity >> 1;
        elements = (T[]) new Object[capacity];
        // TODO: test this
        for (int i = 0 ; i < elements.length; i++) elements[i] = oldArray[i];
    }

    public void testPrint() {
        for (int i = 0; i < size; i++) {
            System.out.print(elements[i] + " ");
        }
        System.out.println();
    }
}
