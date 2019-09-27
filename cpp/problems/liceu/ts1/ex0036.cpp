// TS1 e4 p170 v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    float s = 0;
    for (float i = 0.1; i < 1; i += 0.1) s += i;
    cout << "s = " << s << endl;
    return 0;
}
