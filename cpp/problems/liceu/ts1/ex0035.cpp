// TS1 e4 p170 v1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float s = 0;
    for (int i = 1;  i < 10; i++) s += (float)(i) / 10;
    cout << "s = " << s << endl;
    return 0;
}
