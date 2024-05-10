#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <iostream>

enum ObjectType {
    OT_INT,
    OT_FLOAT,
    OT_BOOL,
    OT_STRING,
    OT_NULL,
    OT_FUNCTION,
    OT_RETURN_VALUE,
    OT_ERROR,
    OT_BUILTIN,
    OT_LIST,
    OT_HASH,
    OT_CLASS,
    OT_INSTANCE,
    OT_FILE,
    OT_SOCKET
};

class AdObject {
public:
    ObjectType type;
    int ref_count;
    bool marked;
    AdObject* next;
    AdObject* prev;

    virtual std::string inspect();
    virtual std::string toString();
};

class AdObjectInteger : public AdObject {
public:
    int value;

    AdObjectInteger();
    AdObjectInteger(int);
    virtual std::string inspect();
    virtual std::string toString();
};

class AdObjectBoolean : public AdObject {
public:
    bool value;

    AdObjectBoolean();
    AdObjectBoolean(bool);
    virtual std::string inspect();
    virtual std::string toString();
};

class AdObjectString : public AdObject {
public:
    std::string value;

    AdObjectString();
    virtual std::string inspect();
    virtual std::string toString();
};

class AdObjectFunction : public AdObject {

};

void Ad_INCREF(AdObject*);
void Ad_DECREF(AdObject*);

void free_memory_AdObject(AdObject*);

#endif