#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <string>

enum ObjectType {
    OBJ_TYPE_NULL,
    OBJ_TYPE_INT,
    OBJ_TYPE_STRING,
    OBJ_TYPE_LIST
};

class PyObject {
public:
    ObjectType type;
    PyObject();
    ~PyObject();
    virtual std::string str();
    virtual std::string repr();
};

class PyObjectString : public PyObject {
private:
    std::string val;
public:
    PyObjectString();
    PyObjectString(std::string s);
    ~PyObjectString();
    std::string str();
    std::string repr();
};

class PyObjectInt : public PyObject {
private:
    int val;
public:
    PyObjectInt();
    PyObjectInt(int i);
    ~PyObjectInt();
    std::string str();
    std::string repr();
};

#endif