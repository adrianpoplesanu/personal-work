/*
   exercise: 039
   page: 238
   description: double linked list
   command: ./program039
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
    Node *head, *tail;
};

void initialize_list(DoubleLinkedList &list) {
    list.head = NULL;
    list.tail = NULL;
}

Node* list_search(DoubleLinkedList list, int k) {
    Node *x = list.head;
    while (x != NULL && x->key != k) {
        x = x->next;
    }
    return x;
}

void list_insert_front(DoubleLinkedList &list, Node *x) {
    x->next = list.head;
    if (list.head != NULL) {
        list.head->prev = x;
    }
    list.head = x;
    x->prev = NULL;
}

void list_delete(DoubleLinkedList list, Node *x) {
    if (x->prev != NULL) {
        x->prev->next = x->next;
    } else {
        list.head = x->next;
    }
    if (x->next != NULL) {
        x->next->prev = x->prev;
    }
}

void print_list(DoubleLinkedList list) {
    Node *current = list.head;
    std::cout << "[ DoubleLinkedList ] ";
    while(current != NULL) {
        std::cout << current->key << " ";
        current = current->next;
    }
    std::cout << "\n";
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

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

