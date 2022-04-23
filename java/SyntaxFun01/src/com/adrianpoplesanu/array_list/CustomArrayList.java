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
        return null;
    }

    @Override
    public void set(int index, T element) {

    }

    @Override
    public void add(T element) {
        if (size >= capacity) {
            growSize();
        }
        elements[size++] = element;
    }

    @Override
    public void remove(int index) {

    }

    private void checkRange(int index) {
        // TODO: if index is out of bounds raise OutOfBounds
    }

    private void growSize() {
        T[] oldArray = elements;
        capacity = capacity >> 1;
        elements = (T[]) new Object[capacity];
        // TODO: just need to copy it over
    }

    private void shrinkSize() {
        // TODO: implement this
    }

    public void testPrint() {
        for (int i = 0; i < size; i++) {
            System.out.print(elements[i] + " ");
        }
        System.out.println();
    }
}
