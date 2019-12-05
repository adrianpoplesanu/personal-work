#include <iostream>
#include <regex>
using namespace std;

int main(int argc, char *argv[]) {
    string s = "for i:numar1:123:1";
    //regex _for("for ([a-zA-Z]+[a-zA-Z0-9]*):([0-9a-zA-Z]+):([0-9a-zA-Z]+):([0-9a-zA-Z]+)");
    regex _for("for ([a-zA-Z0-9]*):([0-9a-zA-Z]+):([0-9a-zA-Z]+):([0-9a-zA-Z]+)");
    smatch m;
    regex_search(s, m, _for);

    for(string x : m) cout << x << " ";
    cout << endl;
    return 0;
}
