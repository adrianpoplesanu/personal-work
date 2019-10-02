#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    vector<int> v(22);
    bool test = !v[6];
    cout << test << endl;
    return 0;
}
