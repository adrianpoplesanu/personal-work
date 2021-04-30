#ifndef __OBJECTS_H
#define __OBJECTS_H
#pragma once

#include <string>

namespace objects {
    enum ObjectType {
        NULL_OBJ,
        INT_OBJ,
        STRING_OBJ,
        FUNCTION_OBJ
    };

    class Object { // a trebuit sa fac totul public pentru ca mostenirea in c++, nu merge cu private, la fel cred ca e si in java
    public:
        ObjectType type;
        Object();
        ~Object();
    };

    class NullObject : public Object{
    public:
        NullObject();
        ~NullObject();
    };

    class IntObject : public Object {
    public:
        int val;
        IntObject();
        IntObject(int);
        ~IntObject();
    };

    class StringObject : public Object {
    public:
        std::string val;
        StringObject();
        StringObject(std::string);
        ~StringObject();
    };
}

#endif