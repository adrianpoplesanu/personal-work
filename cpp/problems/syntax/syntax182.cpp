// array list with template and PyObjects
#include <iostream>

template<typename T>
class ArrayList {
private:
    T *elements;
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
            T *old = elements;
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

    void Print() {
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << elements[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

int main(int argc, char *argv[]) {
    //ArrayList<int> *a = new ArrayList<int>();
    //a->Append(1);
    ArrayList<int> b;
    b.Append(1);
    b.Append(2);
    b.Append(3);
    b.Print();

    ArrayList<std::string> c;
    c.Append("aaa");
    c.Append("bbb");
    c.Append("ccc");
    c.Print();
    return 0;
}
