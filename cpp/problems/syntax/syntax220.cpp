#include <iostream>

struct Obj {
    int type;
};

void DEALLOCATE(Obj* obj) {
    delete obj;
}

int main(int argc, char* argv[]) {
    Obj* obj = new Obj();
    DEALLOCATE(obj);
    return 0;
}
