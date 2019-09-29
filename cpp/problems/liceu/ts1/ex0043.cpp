// TS1 e1 p108 pdf
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[]) {
    random();
    for(int i = 0; i < 10; i++) cout << rand() % 50 << endl;
    return 0;
}
