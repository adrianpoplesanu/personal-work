#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cout << "provide one line argument" << endl;
        return 1;
    }
    char *command = argv[1];
    cout << command << " " << strlen(command) << endl;
    return 0;
}
