package com.adrianpoplesanu.array_list;

import java.util.Arrays;

public class CustomArrayList<T> implements CustomArrayListInterface<T> {
    private int capacity = 4;
    private T[] data;
    int size = 0;

    public CustomArrayList() {
        data = (T[]) new Object[capacity];
    }

    public CustomArrayList(int capacity) {
        this.capacity = capacity;
        data = (T[]) new Object[capacity];
    }

    public CustomArrayList(CustomArrayList<T> oldArray) {
        this.capacity = oldArray.capacity;
        data = Arrays.copyOf(oldArray.data, oldArray.size());
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
    }

    @Override
    public void remove(int index) {

    }

    private void checkRange(int index) {
        // TODO: if index is out of bounds raise OutOfBounds
    }

    private void growSize() {
        T[] oldArray = data;
        capacity = capacity >> 1;
        data = (T[]) new Object[capacity];
        // TODO: just need to copy it over
    }

    private void shrinkSize() {
        // TODO: implement this
    }
}
