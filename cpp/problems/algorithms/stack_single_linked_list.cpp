#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
};

template <typename T>
class Stack {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    Stack() {
        size = 0;
    }
    ~Stack() {
        Node<T>* current = tail;
        while(current) {
            tail = current;
            current = current->prev;
            delete tail;
        }
    }
    void Push(T elem) {
        Node<T>* current = new Node<T>();
        current->data = elem;
        current->prev = tail;
        if (tail == NULL) head = current; 
        tail = current;
        size++;
    }
    T Pop() {
        T result = tail->data;
        Node<T>* current = tail;
        tail = tail->prev;
        size--;
        delete current;
        return result;
    }
    T Top() {
        T result = tail->data;
        return result;
    }
    bool IsEmpty() {
        return size == 0;
    }
    int Size() {
        return size;
    }
    void Print() {
        Node<T>* current = tail;
        while(current) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    std::cout << "running queue implementation...\n";
    Stack<std::string> stack;
    stack.Push("dexiciul");
    stack.Push("ramunitz");
    stack.Push("adrianus");
    stack.Print();
    std::cout << stack.Pop() << "\n";
    stack.Print();
    return 0;
}
