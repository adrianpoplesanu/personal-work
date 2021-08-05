#include <iostream>

template<typename T>
class Stack {
private:
    int capacity;
    int idx;
    T* data;
public:
    Stack() {
        capacity = 3;
        idx = -1;
        data = new T[capacity];
    }
    Stack(int c) {
        capacity = c;
        idx = -1;
        data = new T[c];
    }
    ~Stack() {
        delete[] data;
    }
    void Push(T e) {
        if (idx + 1 == capacity) {
            std::cout << "queue is full\n";
        } else {
            idx++;
            data[idx] = e;
        }
    }
    T Pop() {
        if (idx > -1) {
            idx--;
            return data[idx + 1];
        } else {
            std::cout << "queue is empty";
            T empty;
            return empty;
        }
    }
    T Top() {
        if (idx > -1) {
            return data[idx + 1];
        } else {
            std::cout << "queue is empty";
            T empty;
            return empty;
        }
    }
    bool IsEmpty() {
        return idx == -1;
    }
};

int main(int argc, char* argv[]) {
    Stack<std::string> stack;
    stack.Push("dexiciul");
    stack.Push("ramunitz");
    stack.Push("adrianus");
    stack.Push("buna dimineata");
    std::cout << stack.Pop() << "\n";
    std::cout << stack.Pop() << "\n";
    std::cout << stack.Pop() << "\n";
    std::cout << stack.Pop() << "\n";
    return 0;
}
