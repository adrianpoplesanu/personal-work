#include <iostream>

template<typename T>
struct Node {
    T data;
    Node<T>* next;
};

template<typename T>
class SingleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    SingleLinkedList() {
        size = 0;
    }

    ~SingleLinkedList() {
        Node<T>* current;
        while(head) {
            current = head;
            head = head->next;
            delete current;
        }
    }

    bool IsEmpty() {
        return size == 0;
    }

    int Size() {
        return size;
    }

    void AddFirst(T elem) {
        Node<T>* obj = new Node<T>();
        obj->data = elem;
        size++;
        if (head == NULL) {
            head = obj;
            tail = obj;
        } else {
            obj->next = head;
            head = obj;
        }
    }

    void AddLast(T elem) {
        Node<T>* obj = new Node<T>();
        obj->data = elem;
        size++;
        if (tail) {
            tail->next = obj;
            tail = obj;
        } else {
            head = obj;
            tail = obj;
        }
    }

    T PopFirst() {
        Node<T>* result = head;
        T data = result->data;
        head = head->next;
        size--;
        delete result;
        return data;
    }

    T first() {
        return head;
    }

    T last() {
        return tail;
    }

    void Print() {
        Node<T>* current = head;
        while(current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};
