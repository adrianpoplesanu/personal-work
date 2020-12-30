// ts2 p42 e1
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

void count(map<char, int> &occurances, char ch, int &total) {
    map<char, int>::iterator it = occurances.find(ch);
    if (it == occurances.end() ) {
        occurances.insert(pair<char, int>(ch, 1));
        total++;
    } else {
        it->second++;
        total++;
    }
}

void display(map<char, int> occurances, int total) {
    map<char, int>::iterator it;
    for (it = occurances.begin(); it != occurances.end(); ++it) {
        cout << it->first << " " << it->second << " " << (float)it->second / (float)total * 100 << "%\n";
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "No file given. First argument needs to be a file\n";
        return 1;
    }
    map<char, int> occurances;
    char *filename = argv[1], ch;
    int total = 0;
    ifstream in(filename);
    while(in >> ch) {
        count(occurances, ch, total);
    }
    display(occurances, total);
    return 0;
}

