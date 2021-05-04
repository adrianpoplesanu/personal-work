#include <iostream>

#include "listobject.h"
#include "ad_object.h"
#include "ad_object.cpp"

template<typename T>
Ad_ListObject<T>::Ad_ListObject() {
    type = ad_object::LIST_OBJ;
    octets_num = 1;
    ref_count = 1;
    size = 0;
    capacity = 4;
    ob_elems = new T[capacity];
}

template<typename T>
Ad_ListObject<T>::~Ad_ListObject() {

}

template<typename T>
void Ad_ListObject<T>::Append(T e) {
    if (size < capacity) {
        ob_elems[size++] = e;
    } else {
        // need a resize
    }
}

template<typename T>
void Ad_ListObject<T>::TestPrint() {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        switch(ob_elems[i]->type) {
            case ad_object::NULL_OBJ:
                std::cout << ob_elems[i]->repr();
            break;
            case ad_object::INTEGER_OBJ:
                std::cout << ((ad_object::Ad_IntObject*)ob_elems[i])->repr();
            break;
            case ad_object::BOOLEAN_OBJ:
            break;
            case ad_object::RETURN_VALUE_OBJ:
            break;
            case ad_object::STRING_OBJ:
                std::cout << ((ad_object::Ad_StringObject*)ob_elems[i])->repr();
            break;
            case ad_object::LIST_OBJ:
            break;
        }
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}