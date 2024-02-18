#include <iostream>
#include <ctime>

template <typename T>
class AdList {
public:
    int capacity = 4;
    int size = 0;
    T* elements;

    AdList() {
        elements = new T[capacity];
    }

    void add(T e) {
        if (size >= capacity) {
            capacity *= 2;
            T* newElements = new T[capacity];
            for (int i = 0; i < size; i++) {
                newElements[i] = elements[i];
            }
            T* old = elements;
            elements = newElements;
            delete old;
        }
        elements[size++] = e;
    }

    T get(int i) {
        return elements[i];
    }
};

int main(int argc, char *argv[]) {
    clock_t begin = clock();

    AdList<int*> list;
    int *a = new int(5);

    int i = 0;
    while (i < 100000) {
        list.add(a);
        i++;
    }

    clock_t end = clock();
    std::cout << "ran for: " << double(end - begin) / CLOCKS_PER_SEC << "sec\n";
    return 0;
}
