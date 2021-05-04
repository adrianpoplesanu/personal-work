#include "ad_object.h"

namespace ad_object {
    Ad_Object::Ad_Object() {
        type = NULL_OBJ;
        octets_num = 0;
        ref_count = 1;
    }

    Ad_Object::~Ad_Object() {

    }

    std::string Ad_Object::repr() {
        return "null";
    }

    Ad_IntObject::Ad_IntObject() {
        type = INTEGER_OBJ;
        octets_num = 1;
        ref_count = 1;
        value = 0;
    }

    Ad_IntObject::Ad_IntObject(int i) {
        type = INTEGER_OBJ;
        octets_num = 1;
        ref_count = 1;
        value = i;
    }

    Ad_IntObject::~Ad_IntObject() {

    }

    std::string Ad_IntObject::repr() {
        //return "<int> " + std::to_string(value);
        return std::to_string(value);
    }

    Ad_BooleanObject::Ad_BooleanObject() {
        type = BOOLEAN_OBJ;
        octets_num = 1;
        ref_count = 1;
        value = false;
    }

    Ad_BooleanObject::Ad_BooleanObject(bool b) {
        type = BOOLEAN_OBJ;
        octets_num = 1;
        ref_count = 1;
        value = b;
    }

    Ad_BooleanObject::~Ad_BooleanObject() {

    }

    std::string Ad_BooleanObject::repr() {
        return "aaa";
    }

    Ad_ReturnValueObject::Ad_ReturnValueObject() {
        type = RETURN_VALUE_OBJ;
        octets_num = 1;
        ref_count = 1;
        value = 0x0;
    }

    Ad_ReturnValueObject::~Ad_ReturnValueObject() {

    }

    std::string Ad_ReturnValueObject::repr() {
        return "aaa";
    }

    Ad_StringObject::Ad_StringObject() {
        type = STRING_OBJ;
        octets_num = 1;
        ref_count = 1;
        value = "empty";
    }

    Ad_StringObject::Ad_StringObject(std::string s) {
        type = STRING_OBJ;
        octets_num = 1;
        ref_count = 1;
        value = s;
    }

    Ad_StringObject::~Ad_StringObject() {

    }

    std::string Ad_StringObject::repr() {
        //return "<string> " + value;
        return value;
    }
}