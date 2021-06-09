#include <iostream>
#include <map>

class Node {
public:
    int type;
};

class Int : public Node {
public:
    int value;
};

class String : public Node {
public:
    std::string value;
};

//std::map<std::string, Node> store;
std::map<std::string, Node*> store;

int main(int argc, char *argv[]) {
    Int a;
    a.value = 747;
    String b;
    b.value = "boeing";

    store["obj1"] = &a;
    store["obj2"] = &b;

    //std::cout << &a << "\n";
    //std::cout << &store["obj1"] << "\n";

    //std::cout << "un int: " << ((Int*)&store["obj1"])->value << "\n";
    //std::cout << "un string: " << store["obj2"].value << "\n";
    std::cout << "un int: " << ((Int*)store["obj1"])->value << "\n";
    return 0;
}
