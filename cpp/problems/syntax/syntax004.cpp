#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float g = 4;
    void *ptr = &g;
    cout << *(float *)ptr << endl;
    return 0;
}
