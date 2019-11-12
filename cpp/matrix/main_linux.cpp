#include<iostream>
#include<fstream>
#include<streambuf>
#include<string>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<unistd.h>
using namespace std;

//const int width = 170;
const int width = 100;

const int flipsPerLine = 5;
const int sleepTime = 100000;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int i = 0, x = 0;
    string filename = argv[1];
    //int width = stoi(argv[2]);
    ifstream t(filename);
    std::string source;

    t.seekg(0, std::ios::end);
    source.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    source.assign((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());

    bool switches[width] = {0};
    //memset(switches, 0, width * sizeof(bool));

    int len = source.length();
    unsigned int j = 0;

    system("Color 0A");

    while (true) {
        for (i = 0; i < width; i += 2) {
            if (switches[i]) {
                while (source.at(j) == ' ' || source.at(j) == '\t' || source.at(j) == '\n' || source.at(j) == '\r') {
                    j++;
                    if (j >= len) j = 0;
                }
                //cout << source.at(j) << " ";
                printf("\033[32;1m%c\033[0m ", source.at(j));
                j++;
                if (j >= len) j = 0;
            }
            else {
                cout << "  ";
            }
        }

        for (i = 0; i != flipsPerLine; ++i) {
            x = rand() % width;
            switches[x] = !switches[x];
        }

        cout << endl;

        //this_thread::sleep_for(chrono::milliseconds(sleepTime));
        usleep(sleepTime);

    }
    return 0;
}