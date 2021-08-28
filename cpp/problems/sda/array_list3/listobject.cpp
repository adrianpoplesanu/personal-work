#include <iostream>
#include <sstream>
#include "listobject.h"


PyObjectList::PyObjectList() {
    type = OBJ_TYPE_LIST;
    capacity = 4;
    objs = new PyObject*[capacity];
    size = 0;
};

PyObjectList::~PyObjectList() {
    for (int i = 0; i < size; i++) {
        delete objs[i]; // elibereaza memoria fiecarui element din lista
    }
    delete[] objs; // elibereaza vectorul de adrese care pointeaza catre adresa de memorie a fiecarui element
}

std::string PyObjectList::str() {
    std::string out = "";
    out = out + "[";
    for (int i = 0; i < size; i++) {
        out = out + objs[i]->str();
        if (i < size - 1) out = out + ", ";
    }
    out = out + "]";
    return out;
}

std::string PyObjectList::repr() {
    std::string out = "";
    for (int i = 0; i < size; i++) {
        std::stringstream ss;
        ss << objs[i];
        out = out + ss.str();
        if (i < size - 1) out = out + ", ";
        //std::cout << objs[i] << " ";
    }
    return out;
}

void PyObjectList::append(PyObject *e) {
    if (size < capacity) {
        objs[size++] = e;
    } else {
        upsize();
    }
}

void PyObjectList::upsize() {

}