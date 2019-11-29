#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
    string s = "4412674923756392746";
    int a[10], i = 0;
    for (int i = 0; i < 10; i++) a[i] = 0;
    int _len = s.length();
    int start = _len - 3;
    cout << s << endl;
    i = 0;
    while(start >= 0) {
        //cout << s.substr (start,3) << ":::" << endl;
        a[i] = stoi(s.substr(start, 3));
        i++;
        start -= 3;
        if (start < 0 && start > -3) {
            a[i] = stoi(s.substr(0, 3 + start));
            //cout << s.substr (0, 3 + start) << ":::" << endl;
        }
    }
    for (i = 9; i > -1; i--) cout << setfill('0') << setw(3) << a[i];
    cout << endl;
    return 0;
}
