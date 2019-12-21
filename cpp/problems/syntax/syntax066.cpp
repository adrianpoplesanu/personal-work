#include <iostream>
using namespace std;

class Command {
public:
    Command();
    int PrintA();
private:
    int a;
};

Command::Command() : a(5) {
}

int Command::PrintA() {
    return a;
}

int main(int argc, char *argv[]) {
    Command c;
    cout << c.PrintA() << endl;   
    return 0;
}
