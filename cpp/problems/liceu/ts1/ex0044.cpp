// TS1 e1 p108 pdf v2
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, char * argv[]) {
    srand(time(NULL));
    for(int i = 0; i < 10; i++) {
        int r = rand();
        //cout << r << " " << r % 50 << endl;
        cout << r % 50 << endl;
    }
    return 0;
}
