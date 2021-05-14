#include <iostream>
#include <string>
#include <vector>

enum Ad_Object_Type {
    AD_NULL,
    AD_NUMBER,
    AD_STRING,
    AD_FUNCTION
};

class Ad_Object {
public:
    Ad_Object_Type type;
    Ad_Object() {
        type = AD_NULL;
    }
};

class Ad_Number_Object : public Ad_Object {
public:
    int value;
    Ad_Number_Object() {
        type = AD_NUMBER;
        value = 747;
    }
};

class Ad_String_Object : public Ad_Object {
public:
    std::string value;
    Ad_String_Object() {
        type = AD_STRING;
        value = "drm";
    }
};

class Ad_Function_Object : public Ad_Object {
public:
    std::string value;
    Ad_Function_Object() {
        type = AD_FUNCTION;
        value = "addFunction";
    }
};

int main(int argc, char *argv[]) {
    std::vector<Ad_Object*> objects;
    Ad_Number_Object *a = new Ad_Number_Object();
    Ad_String_Object *b = new Ad_String_Object();
    objects.push_back(a);
    objects.push_back(b);

    for (std::vector<Ad_Object*>::iterator it = objects.begin() ; it != objects.end(); ++it) {
        Ad_Object *generic = *it;
        switch(generic->type) {
            case AD_NULL:
                std::cout << "null\n";
            break;
            case AD_NUMBER:
                std::cout << "<Number> [" << ((Ad_Number_Object*)generic)->value << "]\n";
            break;
            case AD_STRING:
                std::cout << "<String> [" << ((Ad_String_Object*)generic)->value << "]\n";
            break;
            case AD_FUNCTION:
                //...
            break;
        }
    }
    return 0;
}
