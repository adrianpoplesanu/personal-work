#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "hashpair.h"

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
    OT_SOCKET,
    OT_COMPILED_FUNCTION
};

std::unordered_map<ObjectType, std::string> object_type_map = {
    {OT_INT, "INT"},
    {OT_FLOAT, "FLOAT"},
    {OT_BOOL, "BOOL"},
    {OT_STRING, "STRING"},
    {OT_NULL, "NULL"},
    {OT_FUNCTION, "FUNCTION"},
    {OT_RETURN_VALUE, "RETURN_VALUE"},
    {OT_ERROR, "ERROR"},
    {OT_BUILTIN, "BUILTIN"},
    {OT_LIST, "LIST"},
    {OT_HASH, "HASH"},
    {OT_CLASS, "CLASS"},
    {OT_INSTANCE, "INSTANCE"},
    {OT_FILE, "FILE"},
    {OT_SOCKET, "SOCKET"},
    {OT_COMPILED_FUNCTION, "COMPILED_FUNCTION"}
};

class AdObject {
public:
    ObjectType type;
    int ref_count;
    bool marked;
    AdObject* next = NULL;
    AdObject* prev = NULL;

    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

class AdObjectInteger : public AdObject {
public:
    int value;

    AdObjectInteger();
    AdObjectInteger(int);
    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

class AdObjectBoolean : public AdObject {
public:
    bool value;
    bool permanent = false;

    AdObjectBoolean();
    AdObjectBoolean(bool);
    AdObjectBoolean(bool, bool);
    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

class AdObjectNull : public AdObject {
public:
    AdObjectNull();
    ~AdObjectNull();
    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

class AdObjectString : public AdObject {
public:
    std::string value;

    AdObjectString();
    AdObjectString(std::string);
    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

class AdObjectList : public AdObject {
public:
    std::vector<AdObject*> elements;

    AdObjectList();
    AdObjectList(std::vector<AdObject*>);
    ~AdObjectList();
    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

class AdObjectHash : public AdObject {
public:
	std::unordered_map<std::string, HashPair> pairs;

    AdObjectHash();
    AdObjectHash(std::unordered_map<std::string, HashPair>);
    ~AdObjectHash();
    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

class AdObjectFunction : public AdObject {

};

class AdObjectCompiledFunction : public AdObject {
public:
    AdObjectCompiledFunction();
    ~AdObjectCompiledFunction();
    virtual std::string inspect();
    virtual std::string toString();
    virtual std::string hash();
    virtual AdObject* copy();
};

void Ad_INCREF(AdObject*);
void Ad_DECREF(AdObject*);

void free_memory_AdObject(AdObject*);

#endif