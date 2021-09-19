// https://infoarena.ro/problema/desc
#include <iostream>
#include <vector>
using namespace std;

vector<int> divizori;
vector<int> sol;
int total = 0;
int N, k;
int cur_solution = 0;

void desc(int n, int div) {
    if (n == 1) {
        cur_solution++;
        if(cur_solution == k) {
            for (int i = 0; i < divizori.size(); i++) {
                sol.push_back(divizori[i]);
            }
        }
        total++;
    }
    for (int i = div; i <= n; i++) {
        if (n % i == 0) {
            divizori.push_back(i);
            desc(n / i, i);
            divizori.pop_back();
        }
    }
}

int main(int argc, char *argv[]) {
    cout << "N = "; cin >> N;
    cout << "k = "; cin >> k;

    desc (N, 2);
    cout << total << "\n";
    for (int i = 0; i < sol.size(); i++) {
        cout << sol[i] << " ";
    }
    cout << "\n";
    return 0;
}
