/*
   exercise: 41
   page: 239
   description: implement a circular, doubly linked list with a sentinel
   command: ./program041
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int key;
    Node *prev;
    Node *next;
};

struct DoubleLinkedList {
    Node *nil;
};

void initialize_list(DoubleLinkedList &list) {
    list.nil = new Node();
    list.nil->next = list.nil;
    list.nil->prev = list.nil;
}

void list_delete(DoubleLinkedList list, Node* x) {
    x->prev->next = x->next;
    x->next->prev = x->prev;
}

Node* list_search(DoubleLinkedList list, int k) {
    Node *x = list.nil->next;
    while(x != list.nil && x->key != k) {
        x = x->next;
    }
    return x;
}

void list_insert_front(DoubleLinkedList &list, Node* x) {
    x->next = list.nil->next;
    list.nil->next->prev = x;
    list.nil->next = x;
    x->prev = list.nil;
}

void print_list(const DoubleLinkedList &list) {
    Node *current = list.nil->next;
    while(current != list.nil) {
        std::cout << current->key << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void print_node(Node *x) {
    std::cout << "Node{key=" << x->key << ", ";
    std::cout << "prev=" << x->prev->key << ", ";
    std::cout << "next=" << x->next->key << " ";
    std::cout << "}\n";
}

void cleanup_list(DoubleLinkedList &list) {
    Node *current = list.nil->next;
    while(current != list.nil) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    DoubleLinkedList doublelinkedList;
    initialize_list(doublelinkedList);

    Node *elem1 = new Node();
    elem1->key = 11;
    elem1->next = NULL;
    elem1->prev = NULL;

    list_insert_front(doublelinkedList, elem1);

    Node *elem2 = new Node();
    elem2->key = 18;
    elem2->next = NULL;
    elem2->prev = NULL;

    list_insert_front(doublelinkedList, elem2);

    Node *elem3 = new Node();
    elem3->key = 33;
    elem3->next = NULL;
    elem3->prev = NULL;

    list_insert_front(doublelinkedList, elem3);

    print_list(doublelinkedList);

    Node *elem2_search = list_search(doublelinkedList, 18);
    print_node(elem2_search);
    list_delete(doublelinkedList, elem2_search);

    print_list(doublelinkedList);

    cleanup_list(doublelinkedList);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

