#include <iostream>
#include <fstream>
#include "big_number.h"
#include "big_number.cpp"
#include "interpreter.h"
#include "interpreter.cpp"
#include "program.h"
#include "program.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    running();
    BigNumber numar1, numar2, numar3;
    numar1.LoadFromString("44748564589467812374783957123");
    numar2.LoadFromString("17000000000000000000000000000");
    numar3 = numar1 + numar2;
    cout << "\033[29;1mcompiler test:\033[0m ";
    numar3.PrintNumber();
    cout << " ... \033[32;1mok!\033[0m" << endl;
    //cout << " ... ok!" << endl;

    Program program;    
    string command;
    while(1) {
        cout << "> "; 
        getline(cin, command);
        if (command == "help") {
            cout << "=== Help Big Number v1.0 ====================" << endl;
            cout << "help - shows help information" << endl;
            cout << "version - shows compiler version" << endl;
            cout << "exit - exit interpreter ; same as quit" << endl;
            cout << "quit - exit interpreter ; same as exit" << endl;
            cout << "=============================================" << endl;
        }
        if (command == "version") {
            cout << "1.1" << endl;
        }
        if (command == "exit" || command =="quit") {
            cout << "\033[29;1mBye!\033[0m" << endl;
            break;
        }
    }
    return 0;
}
