#include <iostream>
#include <string>
using namespace std;

template<typename T>
struct Node {
    T* info;
    Node<T>* next;
};

template<typename T>
class SingleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    SingleLinkedList() {
        size = 0;
    }
    ~SingleLinkedList() {
	while(head) {
            Node<T>* next = head->next;
            delete head->info; // TODO: i belive this is required, and also cool
            delete head;
            head = next;
        }
    }
    void Append(T elem) {
        if (head) {
            Node<T>* newest = new Node<T>();
            tail->next = newest;
            tail = newest;
            size++;
            tail->info = new T();
            *(tail->info) = elem;
        } else {
            head = new Node<T>();
            tail = head;
            size++;
            head->info = new T();
            *(head->info) = elem;
        }
    }
    void Println() {
        Node<T>* c = head;
        cout << "[";
        while(c) {
            cout << *c->info;
            c = c->next;
            if (c) cout << ", ";
        }
        cout << "]";
        cout << "\n";
    }
};

int main(int argc, char *argv[]) {
    // TODO: finish the implementation
    SingleLinkedList<int> numbers;
    numbers.Append(5);
    numbers.Append(7);
    numbers.Println();

    SingleLinkedList<string> users;
    users.Append("Adrianus");
    users.Append("Dexiciul");
    users.Append("Ramonice");
    users.Println();
    return 0;
}
