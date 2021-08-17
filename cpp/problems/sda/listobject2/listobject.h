#ifndef __LISTOBJECT_H
#define __LISTOBJECT_H

#include "objects.h"

class Ad_List {
private:
    int capacity;
    int size;
    Ad_Object **data;
public:
    Ad_List();
    ~Ad_List();
    int Size();
    bool IsEmpty();
    Ad_Object* Get(int);
    void Set(int, Ad_Object*);
    void Add(int, Ad_Object*);
    Ad_Object* Remove(int);

    bool ValidBounds(int);
    void Inspect();
};

#endif
