// http://info.mcip.ro/?cap=Programare%20dinamica #837
#include <iostream>
#include <string>
using namespace std;

void display(string s, int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << s[a[i]];
    }
    cout << "\n";
}

bool accept(string s, int a[], int k, int n) {
    if (k == 0) return true;
    for (int i = 0; i < k; i++) if (a[i] == a[k]) return false;

    if (s[a[k]] == 'a' || s[a[k]] == 'e' || s[a[k]] == 'i' || s[a[k]] == 'o' || s[a[k]] == 'u') {
        if (s[a[k - 1]] == 'a' || s[a[k - 1]] == 'e' || s[a[k - 1]] == 'i' || s[a[k - 1]] == 'o' || s[a[k - 1]] == 'u') return false;
    }
    if (s[a[k]] != 'a' && s[a[k]] != 'e' && s[a[k]] != 'i' && s[a[k]] != 'o' && s[a[k]] != 'u') {
        if (s[a[k - 1]] != 'a' && s[a[k - 1]] != 'e' && s[a[k - 1]] != 'i' && s[a[k - 1]] != 'o' && s[a[k - 1]] != 'u') return false;
    }
    return true;
}

void back(string s, int a[], int k, int n) {
    if (k == n) {
        display(s, a, n);
    } else {
        a[k] = 0;
        while(a[k] < n) {
            if (accept(s, a, k, n)) {
                back(s, a, k + 1, n);
            }
            a[k]++;
        }
    }
}

int main(int argc, char *argv[]) {
    string s = "cosmina";
    int n = s.length();
    int a[n];
    memset(a, 0, sizeof(a));
    back(s, a, 0, n);
    return 0;
}