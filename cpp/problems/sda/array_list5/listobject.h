#ifndef __LISTOBJECT_H
#define __LISTOBJECT_H

#include "ad_object.h"
#include <vector>

template<typename T> class Ad_ListObject : public ad_object::Ad_Object {
// list object in Ad language
public:
    T *ob_elems; // nu-i place cu T ob_elems[];
    //ad_object::Ad_Object **ob_elems;
    int size;
    int capacity;
    Ad_ListObject();
    ~Ad_ListObject();
    void Append(T);
    void TestPrint();
};

class Ad_ListObject_double_pointer {
// list object in Ad language with double pointer
public:
    ad_object::Ad_Object **ob_elems;
    int size;
    int capacity;
    //Ad_ListObject_double_pointer();
    //~Ad_ListObject_double_pointer();
};

class Ad_ListObject_vector {
// list object in Ad language with vector
public:
    std::vector<ad_object::Ad_Object*> ob_elems;
    //Ad_ListObject_vector();
    //~Ad_ListObject_vector();
};

#endif