#include <iostream>
#include "program.h"
#include "program.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Running Template language REPL...\n";

    Program program;
    program.Run();

    return 0;
}
