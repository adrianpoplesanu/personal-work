// List implementation for Ad language
#include <iostream>

enum ObjectType {
    OT_NULL,
    OT_INTEGER,
    OT_BOOLEAN,
    OT_STRING,
    OT_FUNCTION_LITERAL
};

class Ad_Object {
public:
    ObjectType type;
};

class Ad_Integer_Object : public Ad_Object {
public:
    int value;
    Ad_Integer_Object(int val) {
        type = OT_INTEGER;
        value = val;
    }
};

template<typename T>
class ArrayList {
private:
    T* elems;
    int capacity;
    int size;
};

int main(int argc, char *argv[]) {
    ArrayList<Ad_Object*> al;
    return 0;
}
