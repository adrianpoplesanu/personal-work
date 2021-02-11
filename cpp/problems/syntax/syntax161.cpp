#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    vector<int> v;
    v.push_back(5);
    v.push_back(77);
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";
    return 0;
}
