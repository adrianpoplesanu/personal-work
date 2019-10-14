// !!! This indeed does overflow on a MAC

#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cout << "provide one line argument" << endl;
        return 1;
    }
    char *command = argv[1];
    cout << "attempt overflow" << endl;
    int i = strlen(command) + 1;
    while (i < 1200) { // la 2000 e SEG FAULT
        cout << *(command + i * sizeof(char));
        i++;
    }
    cout << endl;
    return 0;
}
