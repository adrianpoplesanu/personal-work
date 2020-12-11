// ts2 p25 e1
#include <iostream>
using namespace std;

struct deck {
    int id;
    string name;
};

deck build_deck() {
    deck d;
    d.id = 1;
    d.name = "lucky pot";
    return d;
}

int main (int argc, char *argv[]) {
    deck d = build_deck();
    cout << d.id << " " << d.name << "\n";
    return 0;
}
