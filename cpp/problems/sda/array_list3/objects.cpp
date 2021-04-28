#include "objects.h"


PyObject::PyObject() {
    type = OBJ_TYPE_NULL;
}

PyObject::~PyObject() {
    
}

std::string PyObject::str() {
    return "";
}

std::string PyObject::repr() {
    return "";
}

PyObjectString::PyObjectString() {
    type = OBJ_TYPE_STRING;
    val = "";
}

PyObjectString::PyObjectString(std::string s) {
    type = OBJ_TYPE_STRING;
    val = s;
}

std::string PyObjectString::str() {
    return val;
}

std::string PyObjectString::repr() {
    return val;
}

PyObjectInt::PyObjectInt() {
    type = OBJ_TYPE_INT;
    val = 0;
}

PyObjectInt::PyObjectInt(int i) {
    type = OBJ_TYPE_INT;
    val = i;
}

std::string PyObjectInt::str() {
    return std::to_string(val);
}

std::string PyObjectInt::repr() {
    return std::to_string(val);
}