#include <iostream>

enum ObjectType {
    OT_UNDEFINED,
    OT_COMMENT
};

struct Metadata {
    ObjectType type;
};

class Undefined {
public:
    Metadata *info;
    void print() {
        std::cout << "this is an undefined object\n";
    }
};

class Comment {
public:
    Metadata *info;
    void comm() {
        std::cout << "this is a comment\n";
    }
};

int main(int argc, char* argv[]) {
    return 0;
}
