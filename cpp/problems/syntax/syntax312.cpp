#include <iostream>
#include <vector>

class Base {
public:
    int type = 55;
};

class Child : public Base {
public:
    std::string name;
};

void apply(Base *b) {
    Child *c = (Child*) b;
    std::cout << c->type << "\n";
}

int main(int argc, char *argv[]) {
    Child *child = new Child();
    apply(child);
    delete child;

    Child child2;
    apply(&child2);

    return 0;
}
