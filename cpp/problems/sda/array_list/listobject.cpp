#include <iostream>
#include "listobject.h"

template<typename T>
ListObject<T>::ListObject() {
    capacity = 4;
    size = 0;
    elements = new Node<T>[capacity];
}

template<typename T>
ListObject<T>::~ListObject() {
    delete[] elements;
}

template<typename T>
int ListObject<T>::getSize() {
    return size;
}

template<typename T>
void ListObject<T>::append(T e) {
    if (size < capacity) {
        elements[size++].data = e;
    } else {
        capacity *= 2;
        Node<T> *current = elements;
        elements = new Node<T>[capacity];
        for (int i = 0; i < size; i++) elements[i].data = current[i].data;
        elements[size++].data = e;
        delete[] current;
    }
}

template<typename T>
void ListObject<T>::print() {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << elements[i].data;
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

template<typename T>
void ListObject<T>::print_memory_addresses() {
    for (int i = 0; i < size; i++) {
        std::cout << &elements[i] << " " << &(elements[i].data) << "\n";
    }
}

template<typename T>
T ListObject<T>::pop() { // if i return a memory address then i can return null, in this case i return an int, if size = 0 this should be NULL
    // TODO find a way to return null here
    T e = elements[size - 1].data;
    size--; // this should do pop-up
    return e;
}

template<typename T>
T ListObject<T>::first() {
    T e;
    return e;
}

template<typename T>
T ListObject<T>::last() {
    T e;
    return e;
}
