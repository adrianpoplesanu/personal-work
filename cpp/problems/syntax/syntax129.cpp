#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    clock_t start = clock();
    cout << "running\n";
    
    clock_t end = clock();
    cout << "ran for " << double(end-start) / CLOCKS_PER_SEC << "\n";
    return 0;
}
