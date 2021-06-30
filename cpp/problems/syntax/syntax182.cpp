// array list with template and PyObjects
#include <iostream>

template<typename T>
class ArrayList {
private:
    T elements[];
    int size;
    int capacity;
public:
    ArrayList() {
        size = 0;
        capacity = 2;
        elements = new T[capacity];
    }

    void Append(T e) {
        if(size < capacity) {
            elements[size++] = e;
        } else {
            T old[] = elements;
            capacity *= 2;
            elements = new T[capacity];
            for (int i = 0; i < size; i++) elements[i] = old[i];
            delete[] old;
            elements[size++] = e;
        }
    }

    void UpSize() {
        T old[] = elements;
        capacity *= 2;
        elements = new T[capacity];
        for (int i = 0; i < size; i++) elements[i] = old[i];
        delete[] old;
    }

    void DownSize() {
        T old[] = elements;
        capacity /= 2;
        elements = new T[capacity];
        for (int i = 0; i < size; i++) elements[i] = old[i];
        delete[] old;
    }
};

int main(int argc, char *argv[]) {
    return 0;
}
