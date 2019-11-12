#include<iostream>
#include<fstream>
#include<streambuf>
#include<string>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<chrono>

// Width of the matrix line
//const int width = 70;
const int width = 70;

// Defines the number of flips in Boolean Array 'switches'
const int flipsPerLine = 5;

// Delay between two successive line print
const int sleepTime = 100;

using namespace std;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int i = 0, x = 0;
    string filename = "/Users/adrianpoplesanu/Documents/git-projects/personal-work/javascript/caesar3-2/caesar3-2.html";
    ifstream t(filename);
    std::string ch2;

    t.seekg(0, std::ios::end);
    ch2.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    ch2.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());
    cout << ch2.length() << endl;
    for (int i = 0; i < ch2.length(); i++) {
        //cout << ch2.at(i) << endl;
        if (ch2.at(i) != ' ' && ch2.at(i) != '\t' && ch2.at(i) != '\n' && ch2.at(i) != '\r') cout << ch2.at(i);
    }
    return 0;
    int n = 0;
    cout << width;
    while(true) {
        for (i = 0; i < 70; i += 2) {
                cout << ch2.at(n);
        }
        n++;
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }

    return 0;
}
