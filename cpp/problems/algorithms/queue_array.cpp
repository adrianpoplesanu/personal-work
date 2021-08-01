#include <iostream>

template<typename T>
class Queue {
private:
    int capacity;
    int idx;
    T* data;
public:
    Queue() {
        capacity = 3;
        idx = -1;
        data = new T[capacity];
    }
    Queue(int c) {
        capacity = c;
        idx = -1;
        data = new T[c];
    }
    ~Queue() {
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
    Queue<std::string> queue;
    queue.Push("dexiciul");
    queue.Push("ramunitz");
    queue.Push("adrianus");
    queue.Push("buna dimineata");
    std::cout << queue.Pop() << "\n";
    std::cout << queue.Pop() << "\n";
    std::cout << queue.Pop() << "\n";
    std::cout << queue.Pop() << "\n";
    return 0;
}
