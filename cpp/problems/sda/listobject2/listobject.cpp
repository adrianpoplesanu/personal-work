#include "listobject.h"

#include <iostream>

Ad_List::Ad_List() {
    capacity = 4;
    size = 0;
    data = new Ad_Object*[capacity];
}

Ad_List::~Ad_List() {
    //for (int i = 0; i < size; i++) delete data[i];
    delete[] data;
}

int Ad_List::Size() {
    return size;
}

int Ad_List::Capacity() {
    return capacity;
}

bool Ad_List::IsEmpty() {
    return size == 0;
}

Ad_Object* Ad_List::Get(int i) {
    return data[i];
}

void Ad_List::Set(int i, Ad_Object* e) {
    data[i] = e;
}

void Ad_List::Add(int i, Ad_Object* e) {
    if (!ValidBounds(i)) {
        std::cout << "Index out of range\n";
        return;
    }
    if (size == capacity) {
        Resize(capacity * 2);
    }
    for (int j = size - 1; j > i; j--) data[j] = data[j - 1];
    data[i] = e;
    size++;
}

void Ad_List::Append(Ad_Object* obj) {
    Add(size, obj);
}

Ad_Object* Ad_List::Remove(int i) {
    Ad_Object* result = data[i];
    for (int j = i; j < size - 1; j++) {
        data[j] = data[j + 1];
    }
    size--;
    if (size < capacity / 2 && capacity > 4) {
        Resize(capacity / 2);
    }
    return result;
}

bool Ad_List::ValidBounds(int i) {
     if (i < 0 || i > size) {
         return false;
     }
     return true;
}

void Ad_List::Resize(int n) {
    Ad_Object **current = data;
    data = new Ad_Object*[n];
    for (int i = 0; i < size; i++) data[i] = current[i];
    capacity = n;
    delete[] current;
}

void Ad_List::Inspect() {
    std::string out = "[";
    for (int i = 0; i < size; i++) {
        //std::cout << &data[i] << ": " << data[i] << " " << data[i]->Inspect() << " ";
        if (i > 0) out += ", ";
        out += data[i]->Inspect();
    }
    out += "]";
    std::cout << out << "\n";
}
