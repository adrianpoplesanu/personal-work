// Given a string, find the largest substring that is a palindrome
// brute force
#include <iostream>
#include <string>
using namespace std;


bool is_palindrome(string s, int start, int end) {
    while(start <= end) {
        if (s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}

int main(int argc, char *argv[]) {
    string s = "qweaaabbabbaqwe";
    int max = 0, start = 0;
    for (int i = 0; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            if (is_palindrome(s, i, j)) {
                //for (int k = i; k < j; k++) {
                //    cout << s[k];
                //}
                //cout << '\n';
                if (max < j - i + 1) {
                    start = i;
                    max = j - i + 1;
                }
            }
        }
    }
    cout << start << " " << max << "\n";
    for (int i = start; i < start + max; i++) {
        cout << s[i];
    }
    cout << "\n";
    return 0;
}
