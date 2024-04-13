#include <iostream>
#include <memory>

class MemoryUsageTracker {
public:
    int totalAllocated;
    int totalFreed;
    int numAllocations;
    int numFreed;

    MemoryUsageTracker() {
        totalAllocated = 0;
        totalFreed = 0;
        numAllocations = 0;
        numFreed = 0;
    }
};

MemoryUsageTracker memoryUsageTracker;

void* operator new(size_t size) {
    //memoryUsageTracker.numAllocations++;
    //memoryUsageTracker.totalAllocated += size;
    std::cout << "allocating " << size << " bytes\n";
    return malloc(size);
}

void operator delete(void *memory) noexcept {
    //memoryUsageTracker.numFreed++;
    //memoryUsageTracker.totalFreed += sizeof(memory);
    std::cout << "deallocating "<< sizeof(memory) << " bytes\n";
    free(memory);
}

class Test {
public:
    int a, b, c;
    Test() {
        a = 55;
        b = 66;
        c = 77;
    }
    void* operator new(size_t size) {
        memoryUsageTracker.numAllocations++;
        memoryUsageTracker.totalAllocated += size;
        std::cout << "allocating within class " << size << " bytes\n";
        return malloc(size);
    }
    void operator delete(void* ptr) {
        memoryUsageTracker.numFreed++;
        memoryUsageTracker.totalFreed += sizeof(*((Test*)ptr));
        std::cout << "deallocating within class: " << sizeof(*((Test*)ptr)) << " bytes\n";
        free(ptr);
    }
};

int main(int argc, char *argv[]) {
    int *a = new int(5);
    Test *test = new Test();
    std::cout << "sizeof *test: " << sizeof(test) << " bytes\n";
    //std::unique_ptr<Test> obj = std::make_unique<Test>();
    std::cout << "current usage: " << memoryUsageTracker.totalAllocated - memoryUsageTracker.totalFreed << " bytes\n";
    delete a;
    delete test;
    std::cout << "current usage: " << memoryUsageTracker.totalAllocated - memoryUsageTracker.totalFreed << " bytes\n";
    return 0;
}
