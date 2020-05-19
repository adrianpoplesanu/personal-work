#include <iostream>
using namespace std;

struct circle {
    int radius, x, y;
};

int main(int argc, char *argv[]) {
    circle c;
    c.radius = 5;
    c.x = 2;
    c.y = 3;
    cout << c.radius << endl << c.x << endl << c.y << endl;
    circle *p = new circle(); // ooouph, nu se mai face asa
    p->radius = 7;
    p->x = 2;
    p->y = 5;
    cout << p->radius << endl << p->x << endl << p->y << endl;
    return 0;
}
