package com.adrianpoplesanu.array_list;

public interface CustomArrayListInterface<T> {
    int size();
    boolean isEmpty();
    T get(int index);
    void set(int index, T element);
    void add(T element);
    T remove(int index);
}
