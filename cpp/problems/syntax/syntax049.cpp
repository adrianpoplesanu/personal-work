// TO TEST:
// make syntax049
// cat syntax048.cpp | ./syntax049

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string text;
    getline(cin, text);
    cout << "MSG: " << text << endl;
    return 0;
}
