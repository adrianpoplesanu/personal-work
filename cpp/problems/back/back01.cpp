// http://info.mcip.ro/?cap=Programare%20dinamica #874
#include <iostream>
#include <vector>
using namespace std;

vector<int> sol;
int limit;

void back(int div, int n) {
    if (div == limit) return;
    if (div == n) {
        for (std::vector<int>::iterator it = sol.begin() ; it != sol.end(); ++it) std::cout << *it << ' ';
        cout << n << "\n";
    } else if (div < n) {
        if (n % div == 0) {
            sol.push_back(div);
            back(div + 1, n / div);
            sol.pop_back();
            back(div + 1, n);
        }
        else back(div + 1, n);
    }
}

int main(int argc, char *argv[]) {
    int n = 30;
    limit = n;
    back (2, n);
    return 0;
}
