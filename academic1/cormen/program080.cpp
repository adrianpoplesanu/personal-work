/*
   exercise: 080
   page: 492
   description: b-tree search
   command: echo 123 | ./program080
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int n;
    int *keys;
    Node **children;
    bool is_leaf;
};

struct BTree {
    Node *root;
    int t;
};

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here



    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

