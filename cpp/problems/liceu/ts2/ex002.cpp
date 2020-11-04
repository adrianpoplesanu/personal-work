#include <iostream>
using namespace std;

struct book {
    char name[20];
    float price;
    int index;
};

int main (int argc, char *argv[]) {
    book *book1, *book2;
    cout << book1 << "\n";
    cout << book2 << "\n";
    if (book1 == 0x0) {
        cout << "book1 e null\n";
    }
    if (book2 == NULL) {
        cout << "book2 e null\n";
    }
    return 0;
}
