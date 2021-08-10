#include <iostream>

template<typename T>
class Queue {
private:
    int capacity;
    int front;
    int size;
    T* data;
public:
    Queue() {
        capacity = 3;
        front = 0;
        size = 0;
        data = new T[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    bool isEmpty() {
        return size == 0;
    }

    int Size() {
        return size;
    }

    bool enqueue(T e) {
        if (Size() == capacity) {
            return false; // the max capacity of the queue was reached
        } else {
            data[(front + size) % capacity] = e;
            size++;
            return true;
        }
    }

    T dequeue() {
        if (isEmpty()) {
            throw 20;
        } else {
            T res = data[front++];
            size--;
            if (front >= capacity) front -= capacity;
            return res;
        }
    }

    T first() {
        return data[front];
    }
};

int main(int argc, char *argv[]) {
    Queue<std::string> queue;
    queue.enqueue("dexiciul");
    queue.enqueue("e scump");
    std::cout << queue.first() << "\n";
    std::cout << queue.dequeue() << "\n";
    std::cout << queue.dequeue() << "\n";
    queue.enqueue("buna");
    queue.enqueue("dimineata");
    queue.enqueue("!");
    queue.enqueue("test");
    std::cout << queue.dequeue() << "\n";
    std::cout << queue.dequeue() << "\n";
    std::cout << queue.dequeue() << "\n";
    return 0;
}
