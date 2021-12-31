#include <iostream>

struct Obj {
    int type;
};

void DEALLOCATE(void* ptr) {
    free(ptr);
}

int main(int argc, char* argv[]) {
    Obj* obj = (Obj*) malloc(sizeof(Obj));
    DEALLOCATE(obj);

    return 0;
}
