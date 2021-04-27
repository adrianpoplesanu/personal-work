#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <string>

enum ObjectType {
    OBJ_TYPE_INT,
    OBJ_TYPE_STRING
};

class GenericObject {
public:
    ObjectType type;
    virtual void ToString() {
        std::cout << "bla bla bli";
        //std::cout << data;
    }
};

class StringObject : public GenericObject {
public:
    std::string data;
    void ToString() {
        std::cout << data << '\n';
    }
};

class IntObject : public GenericObject {
public:
    int data;
    void ToString() {
        std::cout << data << '\n';
    }
};

#endif