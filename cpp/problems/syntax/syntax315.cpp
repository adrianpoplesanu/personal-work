#include <iostream>
#include <memory>

void* operator new(size_t size) {
    std::cout << "allocating " << size << " bytes\n";
    return malloc(size);
}

void operator delete(void *memory) {
    std::cout << "deallocatingi "<< sizeof(memory) << " bytes\n";
    free(memory);
}

//void operator delete(void *memory, size_t size) {
//    std::cout << "deallocating " << size << " bytes\n";
//    free(memory);
//}

class Test {
public:
    int a, b, c;
    Test() {
        a = 55;
        b = 66;
        c = 77;
    }
};

int main(int argc, char *argv[]) {
    int *a = new int(5);
    Test *test = new Test();
    //std::unique_ptr<Test> obj = std::make_unique<Test>();
    delete a;
    delete test;
    return 0;
}
