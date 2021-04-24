#ifndef __LISTOBJECT_H
#define __LISTOBJECT_H
#pragma once

template<typename T>
struct Node {
    T data;
};

template<typename T>
class ListObject {
private:
    int capacity;
    int size;
    Node<T> *elements;
public:
    ListObject();
    ~ListObject();
    int getSize();
    void append(T e);
    void print();
    void print_memory_addresses();
    T pop();
    T first();
    T last();
    //...
};

#endif