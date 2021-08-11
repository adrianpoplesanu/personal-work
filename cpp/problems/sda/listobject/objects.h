#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <string>

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

#endif
