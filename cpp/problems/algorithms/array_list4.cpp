// List implementation for Ad language
#include <iostream>

enum ObjectType {
    OT_NULL,
    OT_INTEGER,
    OT_BOOLEAN,
    OT_STRING,
    OT_FUNCTION_LITERAL,
    OT_LIST
};

class Ad_Object {
public:
    ObjectType type;
    virtual std::string Inspect();
};

std::string Ad_Object::Inspect() {
    return "not implemented in subclass";
}

class Ad_Integer_Object : public Ad_Object {
public:
    int value;
    Ad_Integer_Object(int val) {
        type = OT_INTEGER;
        value = val;
    }
    virtual std::string Inspect() {
        return std::to_string(value);
    }
};

/*std::string Ad_Integer_Object::Inspect() {
    return std::to_string(value);
}*/

class Ad_String_Object : public Ad_Object {
public:
    std::string value;
    Ad_String_Object(std::string val) {
        type = OT_STRING;
        value = val;
    }
    std::string Inspect() {
        return value;
    }
};

void print_object(Ad_Object* obj) {
    switch(obj->type) {
        case OT_NULL:
            std::cout << "null\n";
        break;
        case OT_INTEGER:
            std::cout << ((Ad_Integer_Object*)obj)->value;
        break;
        case OT_BOOLEAN:
        break;
        case OT_STRING:
             std::cout << ((Ad_String_Object*)obj)->value;
        break;
        case OT_FUNCTION_LITERAL:
        break;
        case OT_LIST:
        break;
    }
}

/*std::string inspect_object(Ad_Object* obj) {
    switch(obj->type) {
        case OT_NULL:
            return "null";
        break;
        case OT_INTEGER:
            return std::to_string(((Ad_Integer_Object*)obj)->value);
        break;
        case OT_BOOLEAN:
            return "todo: boolean inspect";
        break;
        case OT_STRING:
             return ((Ad_String_Object*)obj)->value;
        break;
        case OT_FUNCTION_LITERAL:
             return "todo: function literal inspect";
        break;
    }
}*/

template<typename T>
class ArrayList : public Ad_Object {
private:
    T* elems;
    int capacity;
    int size;

public:
    ArrayList() {
        type = OT_LIST;
        size = 0;
        capacity = 4;
        elems = new T[capacity];
    }
    void Append(T e) {
        elems[size++] = e;
    }
    void Print() {
        for (int i = 0; i < size; i++) {
            print_object(elems[i]);
        }
        std::cout << "\n";
    }
    std::string Inspect() {
        std::string out = "[";
        for (int i = 0; i < size; i++) {
            //print_object(elems[i]);
            if (i > 0) out += ", ";
            out += elems[i]->Inspect();
        }
        out += "]";
        return out;
    }
};

int main(int argc, char *argv[]) {
    ArrayList<Ad_Object*> al;
    Ad_Integer_Object* ob1 = new Ad_Integer_Object(55);
    Ad_String_Object* ob2 = new Ad_String_Object("dexiuciul e scumpet");
    al.Append(ob1);
    al.Append(ob2);
    //al.Print();
    std::cout << al.Inspect() << "\n";
    return 0;
}
