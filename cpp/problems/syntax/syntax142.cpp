#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    cout << system("pwd") << "\n"; // this just prints the response code of the system call
    cout << system("make syntax141") << "\n"; // this just prints the response code of the system call
    cout << system("./syntax141") << "\n"; // this just prints the response code of the system call
    return 0;
}
