#include <iostream>
#include "node.h"
#include "node.cpp"
#include "ast.h"
#include "ast.cpp"
#include "interpreter.h"
#include "interpreter.cpp"
#include "program.h"
#include "program.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "AdriAnus BasiC interpreter 1.0\n";
        cout << ">>> \n";
    }
    if (argc == 2) {
        cout << "file to parse: " << argv[1] << "\n";
    }
    return 0;
}
