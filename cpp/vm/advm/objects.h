#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <iostream>

enum ObjectType {
    OT_INT
};

class AdObject {
public:
    ObjectType type;
    int ref_count;

    virtual std::string inspect();
    virtual std::string toString();
};

class AdObjectInteger : public AdObject {
public:
    int value;

    AdObjectInteger();
    virtual std::string inspect();
    virtual std::string toString();
};


void Ad_INCREF(AdObject*);
void Ad_DECREF(AdObject*);

void free_memory_AdObject(AdObject*);

#endif