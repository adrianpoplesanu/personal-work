#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int n;

int main(int argc, char *argv[]) {
    clock_t start = clock();
    ifstream in;
    ofstream out;
    in.open("problema.in");
    out.open("problema.out");

    //... rezolvarea

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for: " << (double)(end-start) / CLOCKS_PER_SEC << "secs " << endl;
    return 0;
}
