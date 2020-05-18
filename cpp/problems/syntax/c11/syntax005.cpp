#include <iostream>
using namespace std;

struct circle {
    int radius, x, y;
};

int main(int argc, char *argv[]) {
    circle c1;
    c1.radius = 5;
    c1.x = 2;
    c1.y = 3;
    cout << c1.radius << endl << c1.x << endl << c1.y << endl;

    auto c2 = make_shared<circle>();
    c2->radius = 7;
    c2->x = 2;
    c2->y = 5;
    cout << c2->radius << endl << c2->x << endl << c2->y << endl;

    return 0;
}
