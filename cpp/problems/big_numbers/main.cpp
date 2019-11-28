#include <iostream>
#include <fstream>
#include "big_number.h"
#include "big_number.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    running();
    BigNumber numar1, numar2, numar3;
    numar1.LoadFromString("44748564589467812374783957123");
    numar2.LoadFromString("17000000000000000000000000000");
    numar3 = numar1 + numar2;
    cout << "compiler test: ";
    numar3.PrintNumber();
    cout << " ... ok!" << endl;
    
    string command;
    while(1) {
        cout << "> "; 
        getline(cin, command);
        if (command == "help") {
            cout << "===: Help Big Number v1.0 :===" << endl;
        }
        if (command == "version") {
            cout << "1.0" << endl;
        }
        if (command == "exit" || command =="quit") {
            cout << "Bye!" << endl;
            break;
        }
    }
    return 0;
}
