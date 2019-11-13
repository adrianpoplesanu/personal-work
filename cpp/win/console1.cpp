#include <iostream>
#include <Windows.h>
using namespace std;

int main(int argc, char *argv[]) {
    // a program that runs forever in the background
    FreeConsole(); // removes the console link ; but still i need to manually close the console

    while(true) {
        Sleep(10);
    }
    return 0;
}