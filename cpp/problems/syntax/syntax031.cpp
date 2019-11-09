#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string message = "Bla bla bli";
    string cuvant1, cuvant2;
    cout << message.length() << endl;
    getline(cin, cuvant1);
    getline(cin, cuvant2);
    cout << cuvant1 + " * " + cuvant2 << endl;
    return 0;
}
