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

    bool isEmpty() {
        return size == 0;
    }

    void Append(T elem) {
        Node<T>* obj = new Node<T>();
        obj->data = elem;
        if (tail) {
            tail->next = obj;
            tail = obj;
        } else {
            head = obj;
            tail = obj;
        }
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

int main(int argc, char *argv[]) {
    std::cout << "running single linked list implementation...\n";
    SingleLinkedList<std::string> words;
    words.Append("dexiciul");
    words.Append("ramunitz");
    words.Append("adrianus");
    words.Print();
    return 0;
}
