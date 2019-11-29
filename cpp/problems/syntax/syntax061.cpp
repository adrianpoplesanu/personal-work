#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    string s = "a-buna-dimineata!";
    int _len = s.length();
    int start = _len - 3;
    while(start >= 0) {
        cout << s.substr (start,3) << ":::" << endl;
        start -= 3;
        if (start < 0 && start > -3) cout << s.substr (0, 3 + start) << ":::" << endl;
    }
    //cout << s << endl;
    return 0;
}
