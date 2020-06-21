#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "you need one argument: the name of the file you want to cat";
    }
    ifstream in(argv[1]);
    string line;
    while (getline(in, line)) {
        cout << line << "\n";
    }
    return 0;
}
