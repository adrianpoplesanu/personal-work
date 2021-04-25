// nu-mi place
#include <iostream>
#include <string>
using namespace std;

struct Node {
    void* data;
    int id;
    Node* next;
};

void print(Node* head) {
    while(head) {
        if (head->id == 0) {
            cout << *((int*)head->data) << "\n";
        }
        if (head->id == 1) {
            cout << *((string*)head->data) << "\n";
        }
        head = head->next;
    }
}

int main(int argc, char *argv[]) {
    Node* head = new Node();
    head->data = new int(5);
    head->id = 0;
    head->next = 0;

    head->next = new Node();
    head->next->data = new string("neata");
    head->next->id = 1;
    head->next->next = 0;

    print(head);
    return 0;
}
