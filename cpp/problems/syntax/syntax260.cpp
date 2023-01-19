#include <iostream>

class Base {
public:
    int count;
    void printPoints() {
        std::cout << count << "\n";
    }
};

class City : public Base {
public:
    City() {
        count = 2;
    }
};

class Village : public Base {
public:
    Village() {
        count = 1;
    }
};

void changePoints(Base &b) {
    b.count++;
}

int main(int argc, char *argv[]) {
    std::cout << "running colonists...\n";

    City berlin;
    Village paris;

    changePoints(berlin);
    changePoints(paris);

    berlin.printPoints();
    paris.printPoints();

    return 0;
}
