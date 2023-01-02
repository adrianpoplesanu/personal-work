#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <iostream>

enum ObjectTypeEnum {
    INTEGER
};

class Object {
public:
    ObjectTypeEnum type;
    int ref_count;

    virtual std::string inspect();
};

class IntegerObject : public Object {
public:
    int value;

    IntegerObject();
    virtual std::string inspect();
};

#endif