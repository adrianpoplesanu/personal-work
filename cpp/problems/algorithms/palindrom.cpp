#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string s = "acaabbbaaca";
    int n = 11;
    bool is_palindrome = true;
    for (int i = 0; i < n; i++) {
        if (s[i] != s[n - 1 - i]) is_palindrome = false;
    }
    cout << is_palindrome << "\n";
    return 0;
}
