// TS1 e1 p109 pdf
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]) {
    clock_t start, end;
    start = clock();
    do {
        end = clock();
    } while((end - start) / CLOCKS_PER_SEC < 10);
    cout << "The process ran for 10 seconds." << endl;
    return 0;
}
