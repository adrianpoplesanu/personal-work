// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #822

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[20][20];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "," << j << "] = "; cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
