#include <iostream>
using namespace std;

struct elev {
    long grade;
    void afisare() {
        cout << "test " << grade << endl;
    }
};

int main(int argc, char *argv[]) {
    elev e;
    e.grade = 10;
    e.afisare();
    return 0;
}
