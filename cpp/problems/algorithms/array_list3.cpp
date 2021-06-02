#include <iostream>

template<typename T>
struct Node {
    T data;
};

template<typename T>
class ArrayList {
private:
    Node<T> *objs;
    int size;
    int capacity;
public:
    ArrayList() {
        size = 0;
        capacity = 1;
        objs = new Node<T>[capacity];
    }
    ~ArrayList() {
        delete[] objs;
    }
    void Append(T e) {
        if (size < capacity) {
            Node<T> current;
            current.data = e;
            objs[size++] = current;
        } else {
            capacity *= 2;
            Node<T> *old = objs;
            objs = new Node<T>[capacity];
            for (int i = 0; i < size; i++) objs[i] = old[i];
            delete []old;
            Node<T> current;
            current.data = e;
            objs[size++] = current;
        }
    }
    void Remove(T e) {

    }
    int Index(T e) {

    }
    T Pop() {
        
    }
    void Print() {
        for (int i = 0; i < size; i++) {
            std::cout << objs[i].data << " ";
        }
        std::cout << "\n";
    }
};

int main(int argc, char *argv[]) {
    ArrayList<int> numbers;
    numbers.Append(1);
    numbers.Append(2);
    numbers.Append(3);
    numbers.Print();
    ArrayList<std::string> words;
    words.Append("Italia");
    words.Append("Belgia");
    words.Append("Franta");
    words.Print();
    return 0;
}
