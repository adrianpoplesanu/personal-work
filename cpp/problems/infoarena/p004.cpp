#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    clock_t start = clock();
    int n, m, a[16][16];
    ifstream in;
    ofstream out;
    in.open("in004.in");
    out.open("out004.out");

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end-start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}
