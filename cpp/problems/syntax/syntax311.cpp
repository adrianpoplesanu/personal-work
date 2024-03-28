#include <iostream>
#include <vector>

class Base {
public:
    int type = 77; // this is default
    int age = 66;

    void fromBase(Base b) {
        type = b.type;
        age = b.age;
    }

    Base toBase() {
        Base b;
        b.age = age;
        b.type = type;
        return b;
    }
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

Base generate() {
    Parent parent;
    parent.age = 44;
    parent.setType(3);
    return parent;
}

std::vector<Base> generateElements() {
    std::vector<Base> elements;
    Parent p1;
    p1.age = 22;
    elements.push_back(p1);
    Parent p2;
    p2.type = 999;
    elements.push_back(p2);
    return elements;
}

int main(int argc, char *argv[]) {
    Parent parent;
    parent.print();
    parent.setType(5);
    parent.print();
    change(parent);
    parent.print();
    parent.printAge();
    Parent generated;
    generated.fromBase(generate());
    generated.print();
    generated.printAge();

    std::vector<Base> results = generateElements();
    for (int i = 0; i < 2; i++) {
        Parent p;
        p.fromBase(results[i]);
        p.print();
        p.printAge();
    }
    return 0;
}
