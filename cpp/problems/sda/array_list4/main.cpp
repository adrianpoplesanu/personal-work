#include <iostream>
#include <vector>

enum ObjectType {
    NULL_OBJ,
    INT_OBJ,
    STRING_OBJ,
    FUNCTION_OBJ
};

class PyObject {
public:
    ObjectType type;
    //std::string val;
    PyObject() {
        type = NULL_OBJ;
    }
};

class IntObject : public PyObject {
public:
    int val;
    IntObject() {
        type = INT_OBJ;
        val = 0;
    }
};

class StringObject : public PyObject {
public:
    std::string val;
    StringObject() {
        type = STRING_OBJ;
        val = "";
    }
};

int main(int argc, char *argv[]) {
    std::cout << "running...\n";
    std::vector<PyObject*> objects; // as it turns out nu pot sa scap de pointer, e singurul mod in care pot sa fac polimorfism in C/C++
    IntObject a;
    a.val = 5;
    StringObject b;
    b.val = "test";
    objects.push_back(&a);
    objects.push_back(&b);
    for (std::vector<PyObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        std::cout << (*it)->type << ' ';
        //std::cout << it->val << '\n';
        switch((*it)->type) {
            case INT_OBJ:
                std::cout << "int: " << ((IntObject*)(*it))->val; // trebuie sa fac castul, altfel nu am acces la membrii din child
            break;
            case STRING_OBJ:
                std::cout << "string: " << ((StringObject*)(*it))->val; // trebuie sa fac castul, altfel nu am acces la membrii din sub class
            break;
            case NULL_OBJ:
                std::cout << "null object";
            break;
            case FUNCTION_OBJ:
                std::cout << "function: ";
            break;
        }
        std::cout << '\n';
    }
    return 0;
}
