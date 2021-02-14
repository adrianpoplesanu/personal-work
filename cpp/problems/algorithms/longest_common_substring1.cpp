// Given two strings, find the larges common substring
// brute force
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string s1 = "asdsaasdfdsssaaffaaaaaat";
    string s2 = "afsaadsssadssfaaaaaaj";
    //string s1 = "asdsaasdfdsssaaa";
    //string s2 = "afsaadsssadssf";
    int poz1 = -1, poz2 = -1;
    for (int i = 0; i < s1.length(); i++) {
        for (int j = i; j < s1.length(); j++) {
            //for (int k = i; k <= j; k++) cout << s1[k];
            //cout << "\n";
            for(int k = 0; k < s2.length(); k++) {
                bool match = true;
                for(int l = i; l <= j; l++) if (s2[k + l - i] != s1[l]) match = false;
                if (match) {
                    if (j - i > poz2 - poz1) { poz1 = i; poz2 = j; }
                }
            }
        }
    }
    if (poz1 != -1 && poz2 != -1) for (int i = poz1; i <= poz2; i++) cout << s1[i];
    cout << "\n";
    return 0;
}
