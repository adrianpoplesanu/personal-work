#include <iostream>
using namespace std;

struct Node {
    string text;
    Node *next;
};

int main(int argc, char *argv[]) {
    Node *node = new Node();
    node->text = "Buna dimineata!";
    node->next = new Node();
    node->next->text = "Adri";
    node->next->next = new Node();
    node->next->next->text = "an";
    while (node != NULL) {
        cout << node->text << endl;
        node = node->next;
    }
    return 0;
}
