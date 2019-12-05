#include <iostream>
#include <regex>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "running..." << endl;
    string s = "number1:123456789";
    regex variable_assign("([a-zA-Z]+[a-zA-Z0-9]*):([0-9]+)");
    smatch m;
    regex_search(s, m, variable_assign);

    for(string x : m) cout << x << " ";
    cout << endl;
    return 0;
}
