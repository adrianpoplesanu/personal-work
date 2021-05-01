#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T info;
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
        head = 0x0;
        tail = 0x0;
        size = 0;
    }

    ~SingleLinkedList() {
        while(head) {
            Node<T>* current = head;
            head = head->next;
            delete current;
        }
    }

    bool isEmpty() {
        return size == 0;
    }

    void Add(T elem) {
        if (isEmpty()) {
            Node<T>* newest = new Node<T>();
            newest->info = elem;
            head = newest;
            tail = newest;
            size++;
        } else {
            Node<T>* newest = new Node<T>();
            newest->info = elem;
            tail->next = newest;
            tail = newest;
            size++;
        }
    }

    T RemoveFirst() {
        Node<T>* current = head;
        T data = head->info;
        head = head->next;
        delete current;
        return data;
    }

    void Print() {
        Node<T>* current = head;
        std::cout << "[";
        while(current) {
            std::cout << current->info << " " << &(current->next);
            if (current->next) std::cout << ", ";
            current = current->next;
        }
        std::cout << "]\n";
    }
};

void test() {
    SingleLinkedList<int> single_linked_list;
    std::cout << &single_linked_list << "\n";
    single_linked_list.Add(5);
    single_linked_list.Add(4);
    single_linked_list.Add(7);
    single_linked_list.Print();
    int a = single_linked_list.RemoveFirst();
    std::cout << a << "\n";
    single_linked_list.Print();
}

int main(int argc, char *argv[]) {
    test();
    test();
    return 0;
}
