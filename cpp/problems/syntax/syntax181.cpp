// define a single linked list like this one, but one that uses some sort of PyObject and subclass nodes
#include <iostream>
using namespace std;

class PyObject {
public:
    int type;
};

class IntObject : public PyObject {
public:
    //int type;
    int val;
};

class StringObject : public PyObject {
public:
    //...
    string val;
};

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

    void PrintPyObjects() {
        Node<T>* current = head;
        std::cout << "[";
        while (current) {
            //std::cout << current->info->type << " ";
            if (current->info->type == 1) std::cout << ((IntObject*)current->info)->val;
            if (current->info->type == 2) std::cout << ((StringObject*)current->info)->val;
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

void test2() {
    SingleLinkedList<PyObject*> sll;
    IntObject io;
    io.type = 1;
    io.val = 7;
    StringObject so;
    so.type = 2;
    so.val = "test";
    sll.Add(&io);
    sll.Add(&so);
    //sll.Print();
    sll.PrintPyObjects();
}

int main(int argc, char *argv[]) {
    test();
    test();
    test2();
    return 0;
}
