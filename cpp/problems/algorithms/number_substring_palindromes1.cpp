// Given a string, find all the substrings which are palindromes
// brute force
#include <iostream>
using namespace std;

bool check_palindrome(string s, int l, int r) {
    for (int k = 0; k < r - l; k++) {
        if (s[l + k] != s[r - k]) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    string s = "aaabbbaaa";
    int n = 9;
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (check_palindrome(s, i, j)) {
                cout << s.substr(i, j + 1 - i) << "\n";
                count++;
            }
        }
    }
    cout << count << "\n";
    return 0;
}
