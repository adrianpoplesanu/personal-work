/*
   exercise: 041
   page: 238
   description: double linked list with std::unique_ptr
   command: ./program041
*/

#include <iostream>
#include <chrono>
#include <memory>

#define PRINT_EXECUTION_DURATION 0

struct Node {
    int key;
    Node *prev;
    std::unique_ptr<Node> next;
};

struct DoubleLinkedList {
    std::unique_ptr<Node> head;
    Node *tail;
};

void initialize_list(DoubleLinkedList &list) {
    list.head = nullptr;
    list.tail = nullptr;
}

void cleanup_list(DoubleLinkedList &list) {
    list.head.reset();
    list.tail = nullptr;
}

Node* list_search(DoubleLinkedList &list, int k) {
    Node *x = list.head.get();
    while (x != nullptr && x->key != k) {
        x = x->next.get();
    }
    return x;
}

void list_insert_front(DoubleLinkedList &list, int key) {
    std::unique_ptr<Node> x = std::make_unique<Node>();
    x->key = key;
    x->prev = nullptr;
    x->next = std::move(list.head);

    if (x->next != nullptr) {
        x->next->prev = x.get();
    } else {
        list.tail = x.get();
    }

    list.head = std::move(x);
}

void list_delete(DoubleLinkedList &list, Node *x) {
    if (x == nullptr) {
        return;
    }

    std::unique_ptr<Node> *owner = &list.head;
    while (owner->get() != nullptr && owner->get() != x) {
        owner = &((*owner)->next);
    }

    if (owner->get() == nullptr) {
        return;
    }

    std::unique_ptr<Node> removed = std::move(*owner);
    *owner = std::move(removed->next);

    if (*owner != nullptr) {
        (*owner)->prev = removed->prev;
    } else {
        list.tail = removed->prev;
    }
}

void print_list(const DoubleLinkedList &list) {
    Node *current = list.head.get();
    std::cout << "[ DoubleLinkedList ] ";
    while(current != nullptr) {
        std::cout << current->key << " ";
        current = current->next.get();
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    DoubleLinkedList doublelinkedList;
    initialize_list(doublelinkedList);

    list_insert_front(doublelinkedList, 11);
    list_insert_front(doublelinkedList, 18);
    list_insert_front(doublelinkedList, 33);

    print_list(doublelinkedList);

    Node *elem2 = list_search(doublelinkedList, 18);
    list_delete(doublelinkedList, elem2);

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
