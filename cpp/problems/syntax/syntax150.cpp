#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    srand (time(0));
    int i = rand() % 100;
    cout << i << '\n';
    return 0;
}
