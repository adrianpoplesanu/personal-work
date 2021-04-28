#ifndef __LISTOBJECT_H
#define __LISTOBJECT_H
#pragma once

#include "objects.h"
#include "vector"

class PyObjectList : public PyObject {
private:
    int size;
    int capacity;
    PyObject **objs;
public:
    PyObjectList();
    ~PyObjectList();
    std::string str();
    std::string repr();
    void append(PyObject *);
    void insert(PyObject *e, int i) {
        objs[i] = e;
    }
    void upsize();

    /*void print(int n) {
        for (int i = 0; i < n; i++) {
            std::cout << objs[i]->str();
        }
    }*/
};

#endif