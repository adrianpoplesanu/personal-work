// http://info.mcip.ro/?cap=Backtracking #818
#include <iostream>
#include <string>
using namespace std;

void print(string words[], int a[], int m) {
    for (int i = 0; i < m; i++) cout << words[a[i]] << " ";
    cout << "\n";
}

bool accept(string words[], int a[], int n, int m, int k) {
    for (int i = 0; i < k; i++) if (a[i] == a[k]) return false;
    if (k > 0) {
        if (words[a[k - 1]].substr(words[a[k - 1]].length() - 2) == words[a[k]].substr(0, 2)) return true;
    } else {
        return true;
    }
    return false;
}

void back(string words[], int a[], int n, int m, int k) {
    if (k == m) {
        print(words, a, m);
    } else {
        a[k] = 0;
        while(a[k] < n) {
            if (accept(words, a, n, m, k)) {
                back(words, a, n, m, k + 1);
            }
            a[k]++;
        }
    }
}

int main(int argc, char *argv[]) {
    int n = 8, m = 3;
    string words[] = {"paul", "alina", "asfalt", "nas", "ultim", "imagine", "nasture", "real"};
    int a[n];
    memset(a, 0, sizeof(a));
    back(words, a, n, m, 0);
    return 0;
}