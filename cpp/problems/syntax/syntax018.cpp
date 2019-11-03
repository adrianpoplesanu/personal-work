#include <iostream>
using namespace std;

typedef struct {
    char *text;
} Element;

int main(int argc, char *argv[]) {
    Element element;
    element.text = "Buna dimineata!";
    cout << element.text << endl;
    return 0;
}
