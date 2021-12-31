#include <iostream>
#include <cstdlib>

struct Obj {
    int type;
};

void DEALLOCATE(void* ptr) {
    std::free(ptr);
}

int main(int argc, char* argv[]) {
    Obj* obj = (Obj*) std::malloc(sizeof(Obj));
    DEALLOCATE(obj);

    return 0;
}
