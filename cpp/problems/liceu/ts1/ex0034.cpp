// TS1 e3 p103 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    // the for loop block is evaluated n-1 times
    // but the condition is evaluated n times
    // n = 3
    // i = 1, sum updates - for condition evaluation: true
    // i = 2, sum updates - for condition evaluation: true
    // i = 3, sum updates - for condition evaluatrion: false -> exit loop
    // only 2 passes in the loop but 3 condition checks
    // that's why it works!
    int n, s = 0;
    cout << "n = "; cin >> n;
    for(int i = 0; s+=++i,cout<<i<<endl,i<n; ) ; // this looks weird but is correct
    cout << "s = " << s << endl;
    s = 0;
    for(int i = 1; s+=i++,cout<<i<<endl,i<=n; ) ; // this looks weird but is correct
    cout << "s = " << s << endl;
    return 0;
}
