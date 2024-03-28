#include <iostream>

class Base {
protected:
    int type = 77; // this is default
public:
    int age = 66;
};

class Parent : public Base {
public:
    void setType(int t) {
        type = t;
    }

    void print() {
        std::cout << type << "\n";
    }

    void printAge() {
        std::cout << age << "\n";
    }
};

void change(Base base) {
    base.age = 88;
}

int main(int argc, char *argv[]) {
    Parent parent;
    parent.print();
    parent.setType(5);
    parent.print();
    change(parent);
    parent.print();
    parent.printAge();
    return 0;
}
