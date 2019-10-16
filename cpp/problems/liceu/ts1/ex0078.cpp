// TS1 e26 p112 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int z1, z2, l1, l2, a1, a2;
    char date1[10], date2[10];
    // cum se citeau stringurile de la tastatura?
    //cout << "date1 = "; cin.get(date1, 10);
    //cout << "date2 = "; cin.get(date2, 10);
    cout << " date1 = "; cin.getline(date1, 10); cin.get();
    cout << " date2 = "; cin.getline(date2, 10);
    cout << date1 << " " << date2 << endl;
    return 0;
}
