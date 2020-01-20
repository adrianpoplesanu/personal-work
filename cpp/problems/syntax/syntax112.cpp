#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    char str[] = "tester";
    memset(str, 'a', sizeof(str) - 1);
    cout << str << endl;
    return 0;
}
