#ifndef __LISTOBJECT_H
#define __LISTOBJECT_H
#pragma once

#include "objects.h"
#include "vector"

class ListObject {
public:
    int size;
    GenericObject **e;
    ListObject() {
        //e = (GenericObject **)malloc(10 * sizeof(GenericObject*)); // this works
        e = new GenericObject*[10]; // this also works
        size = 0;
    }
    void insert(GenericObject *go, int i) {
        e[i] = go;
    }

    void print(int n) {
        for (int i = 0; i < n; i++) {
            e[i]->ToString();
        }
        /*if (e->type == OBJ_TYPE_INT) {
            //IntObject *shape = e;
            //shape->ToString();
            e->ToString();
        }
        if (e->type == OBJ_TYPE_STRING) {
            e->ToString();
        }*/
    }
};

#endif