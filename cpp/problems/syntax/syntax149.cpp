#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    srand (time(NULL));
    int i = rand() % 100;
    cout << i << '\n';
    return 0;
}
