// TS1 e7 p105 pdf v1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, inv;
    cout << "n = "; cin >> n;
    for(; inv*=10,inv+=n%10,n/=10,n; ) ;
    cout << "inv = " << inv << endl;
    return 0;
}
