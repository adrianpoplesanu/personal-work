#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <iostream>
#include <map>
#include "big_number.h"

enum ObjectType {
    OT_NULL,
    OT_BIG_NUMBER
};

std::map<ObjectType, std::string> object_type_converter = {
    {OT_NULL, "NullObject"},
    {OT_BIG_NUMBER, "BigNumberObject"}
};

class BNObject {
    public:
        ObjectType type;
        int ref_count;
        unsigned int octets;

        virtual ObjectType getType();
        virtual std::string inspect();
        virtual std::string hash();
        virtual BNObject* copy();
};

class BNBigNumberObject : BNObject {
    public:
        BigNumber number;

        BNBigNumberObject();
        BNBigNumberObject(BigNumber);
        ~BNBigNumberObject();

        virtual ObjectType getType();
        virtual std::string inspect();
        virtual std::string hash();
        virtual BNObject* copy();
};

void BN_INCREF(BNObject*);
void BN_DECREF(BNObject*);
void free_BN_object_memory(BNObject*);

#endif