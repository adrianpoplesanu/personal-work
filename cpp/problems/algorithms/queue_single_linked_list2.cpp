#include <iostream>
#include "single_linked_list2.cpp"

template<typename T>
class SingleLinkedListQueue {
private:
    SingleLinkedList<T> list;
public:
    SingleLinkedListQueue() {

    }

    ~SingleLinkedListQueue() {

    }

    bool isEmpty() {
        return list.IsEmpty();
    }

    int size() {
        return list.Size();
    }

    void enqueue(T e) {
        list.AddLast(e);
    }

    T dequeue() {
        T res = list.PopFirst();
        return res;
    }

    T first() {
        return list.first();
    }
};

int main(int argc, char *argv[]) {
    SingleLinkedListQueue<std::string> queue;
    queue.enqueue("bebe");
    queue.enqueue("dex");
    queue.enqueue("e scump");

    while(!queue.isEmpty()) {
        std::cout << queue.dequeue() << "\n";
    }

    return 0;
}
