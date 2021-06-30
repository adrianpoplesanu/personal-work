// array list with template and PyObjects
#include <iostream>

enum ObjectType {
    OT_INTEGER,
    OT_STRING
};

class Ad_Object {
public:
    ObjectType type;
};

class Ad_Int_Object : public Ad_Object {
public:
    int value;
    Ad_Int_Object() {
        type = OT_INTEGER;
    }
};

class Ad_String_Object : public Ad_Object {
public:
    std::string value;
    Ad_String_Object() {
        type = OT_STRING;
    }
};

template<typename T>
class ArrayList {
private:
    T *elements;
    int size;
    int capacity;
public:
    ArrayList() {
        size = 0;
        capacity = 2;
        elements = new T[capacity];
    }

    void Append(T e) {
        if(size < capacity) {
            elements[size++] = e;
        } else {
            T *old = elements;
            capacity *= 2;
            elements = new T[capacity];
            for (int i = 0; i < size; i++) elements[i] = old[i];
            delete[] old;
            elements[size++] = e;
        }
    }

    void UpSize() {
        T old[] = elements;
        capacity *= 2;
        elements = new T[capacity];
        for (int i = 0; i < size; i++) elements[i] = old[i];
        delete[] old;
    }

    void DownSize() {
        T old[] = elements;
        capacity /= 2;
        elements = new T[capacity];
        for (int i = 0; i < size; i++) elements[i] = old[i];
        delete[] old;
    }

    void Print() {
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << Print_Ad_Object(elements[i]);
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    std::string Print_Ad_Object(T e) {
        if ((*e).type == OT_INTEGER) {
            return std::to_string(((Ad_Int_Object*)e)->value);
        }
        if ((*e).type == OT_STRING) {
            return ((Ad_String_Object*)e)->value;
        }
        return "default";
    }
};

int main(int argc, char *argv[]) {
    ArrayList<Ad_Object*> items;
    Ad_Int_Object *obj1 = new Ad_Int_Object();
    (*obj1).value = 1;
    Ad_String_Object *obj2 = new Ad_String_Object();
    (*obj2).value = "adrianus";
    items.Append(obj1);
    items.Append(obj2);
    items.Print();
    return 0;
}
