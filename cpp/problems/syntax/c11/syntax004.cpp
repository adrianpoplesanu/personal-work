#include <iostream>
using namespace std;

class Circle {
public:
    int radius, x, y;
};

int main(int argc, char *argv[]) {
    auto circle = make_shared<Circle>();
    circle->radius = 5;
    circle->x = 2;
    circle->y = 3;
    cout << circle << endl;
    cout << circle->radius << endl;
    cout << circle->x << endl;
    cout << circle->y << endl;
    cout << typeid(circle).name() << endl;
    return 0;
}
