#include <iostream>

#include "single_linked_list2.cpp"

template<typename T>
class SingleLinkedListStack {
private:
    SingleLinkedList<T> list;
    int size;
public:
    SingleLinkedListStack() {
        size = 0;
    }

    ~SingleLinkedListStack() {

    }

    void Push(T e) {
        list.AddFirst(e);
    }

    T Top() {
        return list.first();
    }

    T Pop() {
        T result = list.PopFirst();
        return result;
    }

    bool IsEmpty() {
        return list.IsEmpty();
    }

    int Size() {
        return size;
    }
};

int main(int argc, char *argv[]) {
    SingleLinkedListStack<std::string> stack;

    std::cout << stack.Size() << "\n";
    std::cout << stack.IsEmpty() << "\n";

    stack.Push("bebe");
    stack.Push("dex");
    std::cout << stack.Top() << "\n";
    stack.Push("e");
    stack.Push("scump");

    while (!stack.IsEmpty()) {
        std::cout << stack.Pop() << "\n";
    }

    return 0;
}
