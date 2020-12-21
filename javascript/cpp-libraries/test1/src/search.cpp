#include <vector>
using namespace std;

int search(vector<int> v, int item) {
    int found = 0;
    for (unsigned long i = 0; i < v.size(); ++i) {
        if (v.at(i) == item) ++found;
    }
    return found;
}
