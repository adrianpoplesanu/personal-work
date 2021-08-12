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
    Ad_Object* get(int);
    void set(int, Ad_Object*);
    void add(Ad_Object*);
    Ad_Object* remove(int);

    void Inspect();
};

#endif
