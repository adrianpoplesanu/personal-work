#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string prompt = "Input something: ", name, hello = "Hello ";
    cout << prompt << endl;
    getline(cin, name);
    cout << hello + name << endl;
    return 0;
}
