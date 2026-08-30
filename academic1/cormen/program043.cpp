/*
   exercise: 043
   page: 240
   description: reverse singly linked list
   command: ./program043
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int key;
    Node *next;
};

struct LinkedList {
    Node *head;
    Node *tail;
};

void initialize_list(LinkedList &list) {
    list.head = NULL;
    list.tail = NULL;
}

void list_insert_front(LinkedList &list, Node *x) {
    x->next = list.head;
    list.head = x;
}

void list_delete(LinkedList &list, Node *x) {
    Node *y = list.head;
    while (y != NULL && y->next != x) {
        y = y->next;
    }
    if (y != NULL) {
        y->next = x->next;
    }
}

void list_reverse(LinkedList &list) {
    Node *x = list.head;
    Node *y = NULL;
    while (x != NULL) {
        Node *z = x->next;
        x->next = y;
        y = x;
        x = z;
    }
    list.head = y;
}

void print_list(LinkedList &list) {
    Node *x = list.head;
    std::cout << "List: ";
    while (x != NULL) {
        std::cout << x->key << " ";
        x = x->next;
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    LinkedList list;
    initialize_list(list);

    Node *el1 = new Node();
    el1->key = 1;
    list_insert_front(list, el1);

    Node *el2 = new Node();
    el2->key = 2;
    list_insert_front(list, el2);
    
    Node *el3 = new Node();
    el3->key = 3;
    list_insert_front(list, el3);
    
    print_list(list);
    list_reverse(list);
    print_list(list);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

