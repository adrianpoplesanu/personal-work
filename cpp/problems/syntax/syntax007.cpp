#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 0; i < 5; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < 5; ++i) cout << i << " ";
    cout << endl;
    for (int i = 0; i++ < 5; ) cout << i << " ";
    cout << endl; 
    return 0;
}
