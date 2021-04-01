#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    char current_char = 'c';
    cout << (('a' <= current_char) && (current_char <= 'z')) << "\n";
    cout << (('A' <= current_char) && (current_char <= 'Z')) << "\n";
    cout << ((current_char == '_')) << "\n";
    return 0;
}
