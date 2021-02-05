#include <iostream>
using namespace std;

struct Cerc {
    float x, y;
    int raza;
};

int main(int argc, char *argv[]) {
    Cerc c;
    cout << c.x << " " << c.y << " " << c.raza << "\n";
    c.x = 1.2f;
    c.y = 2.3f;
    c.raza = 4;
    cout << c.x << " " << c.y << " " << c.raza << "\n";

    Cerc *p = new Cerc();
    p->x = 1.1;
    p->y = 2.1;
    p->raza = 2;
    cout << p->x << " " << p->y << " " << p->raza << "\n";

    cout << (*p).x << " " << (*p).y << " " << (*p).raza << "\n";

    return 0;
}
