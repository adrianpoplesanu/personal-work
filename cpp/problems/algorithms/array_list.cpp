#include <iostream>
#include <string>
using namespace std;

template<typename T>
struct Node {
    T data;
};

template<typename T>
class ArrayList {
private:
    Node<T> *objects;
    int size;
    int capacity;
    int index;
public:
    ArrayList() {
        size = 0;
        index = 0;
        capacity = 1;
        objects = new Node<T>[capacity];
    }
    ~ArrayList() {
        delete[] objects;
    }
    int getCapacity() {
        return capacity;
    }
    void resize() {
        Node<T> *temp = new Node<T>[2 * capacity];
        //memset(temp, 0, sizeof(temp));
        for (int i = 0; i < capacity; i++) temp[i] = objects[i];
        capacity *= 2;
        delete[] objects; // asta e important, daca nu il pun aici, o sa am memory leak
        objects = temp;
    }
    void add(T data) {
        if (size == capacity) resize();
        Node<T> newest;
        newest.data = data;
        objects[index++] = newest;
        size++;
    }
    T getAt(int i) {
        return objects[i].data;
    }
    void print() {
        cout << "[";
        if (size > 0) {
            for (int i = 0; i < size - 1; i++) cout << objects[i].data << ", ";
            cout << objects[size - 1].data;
        }
        cout << "]\n";
    }
    void print_memory_addresses() {
        cout << "objects: ";
        for (int i = 0; i < size; i++) cout << &objects[i] << " ";
        cout << "\n";
    }
};

void test_memory() {
    ArrayList<string> *words = new ArrayList<string>();
    //int *c = new int(4);
    cout << words->getCapacity() << "\n";
    words->add("dexiciul");
    words->add("ramonice");
    words->add("adrianus");
    cout << words->getCapacity() << "\n";
    words->print();
    string test = words->getAt(1);
    cout << test << "\n";
    //int *a = new int(5);
    words->print_memory_addresses();
    delete words;
    //free(words);
    //int *b = new int(6);
    //cout << "int pointers: " << c << " " << a << " " << b << "\n";
    //free(a);
    //free(b);
    //free(c);
}

int main(int argc, char *argv[]) {
    int *a = new int(1);
    test_memory();
    test_memory();
    int *b = new int(2);
    cout << "main pointers: " << a << " " << b << "\n";
    return 0;
}