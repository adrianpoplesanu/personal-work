#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
    string line;
    int i = 0;
    while(!cin.eof()) {
        getline(cin, line);
        cout << "\033[0;31m" << setfill('0') << setw(5) << i++ << "\033[0m: " << "\033[0;32m" << line << "\033[0m" << endl;
    }
    return 0;
}
