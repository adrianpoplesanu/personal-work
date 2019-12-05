#include <iostream>
#include <regex>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "running..." << endl;
    //string s = "number1:123456789";
    //string s = "number1:1233456 ";
    string s = "number1:123 234";
    regex variable_assign("([a-zA-Z]+[a-zA-Z0-9]*):([0-9a-zA-Z]+)");
    smatch m;
    regex_search(s, m, variable_assign);

    if (s == m[0]) cout << "e valid!" << endl;
    else cout <<"invalid!" << endl;

    for(string x : m) cout << x << " ";
    cout << endl;
    return 0;
}
