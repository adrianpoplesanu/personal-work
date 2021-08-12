#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <string>
#include "listobject.h"

enum ObjectType {
    OT_NULL,
    OT_INTEGER,
    OT_STIRNG,
    OT_FUNCTION,
    OT_LISTOBJECT
};

class Ad_Object {
public:
    int ref_count;
    ObjectType type;
    virtual std::string Inspect();
    virtual ObjectType Type();
    virtual void Print();
};

class Ad_Null_Object : Ad_Object {
public:
    Ad_Null_Object();
    ~Ad_Null_Object();
    virtual std::string Inspect();
    virtual ObjectType Type();
    virtual void Print();
};

class Ad_Integer_Object : Ad_Object {
public:
    int value;

    Ad_Integer_Object();
    Ad_Integer_Object(int);
    ~Ad_Integer_Object();
};

class Ad_String_Object : Ad_Object {
public:
    std::string value;

    Ad_String_Object();
    Ad_String_Object(std::string);
    ~Ad_String_Object();
};

class Ad_List_Object : Ad_Object {
public:
    Ad_List<Ad_Object*> list;

    Ad_List_Object();
    ~Ad_List_Object();
};

#endif
