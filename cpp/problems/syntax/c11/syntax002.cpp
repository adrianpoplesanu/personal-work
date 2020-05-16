#include <iostream>
using namespace std;

class Circle {
public:
    int radius, x, y;
};

int main(int argc, char *argv[]) {
    //auto *p = make_shared<Circle>();
    Circle *p = new Circle();
    cout << p << endl;
    cout << typeid(p).name() << endl;
    return 0;
}
