/*
   exercise: 044
   page: 244
   description: doubly linked list using three arrays
   command: ./program044
*/

#include <iostream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

const int NIL = -1;
const int N = 50;

struct DoubleLinkedList {
    int key[N];
    int next[N];
    int prev[N];
    int head;
    int free;
};

void initialize_list(DoubleLinkedList &list) {
    list.head = NIL;
    list.free = 0;
    for (int i = 0; i < N - 1; i++) {
        list.next[i] = i + 1;
        list.prev[i] = NIL;
        list.key[i] = 0;
    }
    list.next[N - 1] = NIL;
    list.prev[N - 1] = NIL;
    list.key[N - 1] = 0;
}

int allocate_object(DoubleLinkedList &list) {
    if (list.free == NIL) {
        std::cout << "[ ERROR ] out of space\n";
        return NIL;
    }
    int x = list.free;
    list.free = list.next[x];
    return x;
}

void free_object(DoubleLinkedList &list, int x) {
    list.next[x] = list.free;
    list.free = x;
}

int list_search(DoubleLinkedList &list, int k) {
    int x = list.head;
    while (x != NIL && list.key[x] != k) {
        x = list.next[x];
    }
    return x;
}

void list_insert_front(DoubleLinkedList &list, int x) {
    list.next[x] = list.head;
    if (list.head != NIL) {
        list.prev[list.head] = x;
    }
    list.head = x;
    list.prev[x] = NIL;
}

void list_delete(DoubleLinkedList &list, int x) {
    if (x == NIL) {
        return;
    }
    if (list.prev[x] != NIL) {
        list.next[list.prev[x]] = list.next[x];
    } else {
        list.head = list.next[x];
    }
    if (list.next[x] != NIL) {
        list.prev[list.next[x]] = list.prev[x];
    }
    free_object(list, x);
}

void print_list(DoubleLinkedList &list) {
    int x = list.head;
    std::cout << "[ DoubleLinkedList ] ";
    while (x != NIL) {
        std::cout << list.key[x] << " ";
        x = list.next[x];
    }
    std::cout << "\n";
}

void print_arrays(DoubleLinkedList &list, int n) {
    std::cout << "head=" << list.head << " free=" << list.free << "\n";
    std::cout << "index: ";
    for (int i = 0; i < n; i++) {
        std::cout << i << " ";
    }
    std::cout << "\nkey:   ";
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(3) << list.key[i] << " ";
    }
    std::cout << "\nnext:  ";
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(3) << list.next[i] << " ";
    }
    std::cout << "\nprev:  ";
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(3) << list.prev[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    DoubleLinkedList list;
    initialize_list(list);

    int elem1 = allocate_object(list);
    list.key[elem1] = 11;
    list_insert_front(list, elem1);

    int elem2 = allocate_object(list);
    list.key[elem2] = 18;
    list_insert_front(list, elem2);

    int elem3 = allocate_object(list);
    list.key[elem3] = 33;
    list_insert_front(list, elem3);

    print_list(list);
    print_arrays(list, 6);

    int found = list_search(list, 18);
    std::cout << "[ DELETING ] " << list.key[found] << "\n";
    list_delete(list, found);

    print_list(list);
    print_arrays(list, 6);

    int elem4 = allocate_object(list);
    list.key[elem4] = 44;
    list_insert_front(list, elem4);

    print_list(list);
    print_arrays(list, 6);

    int found2 = list_search(list, 44);
    std::cout << "[ DELETING ] " << list.key[found2] << "\n";
    list_delete(list, found2);

    print_list(list);
    print_arrays(list, 6);
    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
