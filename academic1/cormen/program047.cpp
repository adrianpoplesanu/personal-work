/*
   exercise: 047
   page: 254
   description: direct address tables
   command: ./program047
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int key;
    int value;
};

Node* direct_address_seach(Node* T[], int n, int k) {
    return T[k];
}

void direct_address_insert(Node* T[], int n, Node *x) {
    T[x->key] = x;
}

void direct_address_delete(Node* T[], int n, Node *x) {
    T[x->key] = nullptr;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    Node* T[50];
    int n = 50;

    Node *el1 = new Node();
    el1->key = 1;
    el1->value = 11;

    direct_address_insert(T, n, el1);

    Node *search1 = direct_address_seach(T, n, 1);
    if (search1) {
        std::cout << "Search 1 found: " << search1->value << std::endl;
    } else {
        std::cout << "Search 1 not found" << std::endl;
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

