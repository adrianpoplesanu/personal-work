#include "listobject.h"

#include <iostream>

Ad_List::Ad_List() {
    capacity = 4;
    data = new Ad_Object*[capacity];
}

Ad_List::~Ad_List() {

}

int Ad_List::Size() {
    return size;
}

bool Ad_List::IsEmpty() {
    return size == 0;
}

Ad_Object* Ad_List::get(int i) {
    return data[i];
}

void Ad_List::set(int i, Ad_Object* e) {
    data[i] = e;
}

void Ad_List::add(int i, Ad_Object* e) {
    if (!ValidBounds(i)) {
        std::cout << "Index out of range\n";
        return;
    }
    if (size == capacity) {
        std::cout << "list resize\n";
        Ad_Object **current = data;
        capacity *= 2;
        data = new Ad_Object*[capacity];
        for (int j = 0; j < capacity / 2; j++) data[j] = current[j];
        delete[] current;
    }
    for (int j = size - 1; j > i; j--) data[j] = data[j - 1];
    data[i] = e;
    size++;
}

Ad_Object* Ad_List::remove(int i) {
    return NULL;
}

bool Ad_List::ValidBounds(int i) {
     if (i < 0 || i > size) {
         return false;
     }
     return true;
}

void Ad_List::Inspect() {
    for (int i = 0; i < size; i++) {
        std::cout << &data[i] << ": " << data[i] << " " << data[i]->Inspect() << " ";
    }
    std::cout << "\n";
}
