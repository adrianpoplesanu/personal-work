#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    string seed = system("python ../../../python/utils/random.py");
    cout << seed << '\n';
    return 0;
}
