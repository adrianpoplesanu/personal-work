#ifndef __AD_OBJECT_H
#define __AD_OBJECT_H
#include <string>

namespace ad_object {
    enum Ad_Object_Type {
        NULL_OBJ,
        INTEGER_OBJ,
        BOOLEAN_OBJ,
        RETURN_VALUE_OBJ,
        STRING_OBJ,
        LIST_OBJ
    };

    class Ad_Object {
        // generic object for Ad language
    public:
        Ad_Object_Type type;
        unsigned int octets_num;
        unsigned int ref_count;
        Ad_Object();
        ~Ad_Object();
        std::string repr();
    };

    class Ad_IntObject : public Ad_Object {
    public:
        int value;
        Ad_IntObject();
        Ad_IntObject(int);
        ~Ad_IntObject();
        std::string repr();
    };

    class Ad_BooleanObject : public Ad_Object {
    public:
        bool value;
        Ad_BooleanObject();
        Ad_BooleanObject(bool);
        ~Ad_BooleanObject();
        std::string repr();
    };

    class Ad_ReturnValueObject : public Ad_Object {
    public:
        Ad_Object* value;
        Ad_ReturnValueObject();
        ~Ad_ReturnValueObject();
        std::string repr();
    };

    class Ad_StringObject : public Ad_Object {
    public:
        std::string value;
        Ad_StringObject();
        Ad_StringObject(std::string);
        ~Ad_StringObject();
        std::string repr();
    };

    void Ad_INCREF(Ad_Object*);
    void Ad_DECREF(Ad_Object*);
}

#endif