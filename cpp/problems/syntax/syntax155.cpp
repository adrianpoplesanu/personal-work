#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
using namespace std;

string exec(const char* cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int main (int argc, char *argv[]) {
    string output = exec("python ../../../python/utils/random.py");
    //cout << "original seed " << output << '\n';
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
    //cout << "5 digit number seed " << output.substr(output.length() - 5) << '\n';
    string remainder = output.substr(output.length() - 5);
    int seed = stoi(remainder);
    //cout << num << '\n';
    
    if (argc != 2) {
        cout << "mininum one argument needed";
        return 1;
    } else {
        char* p;
        long arg = strtol(argv[1], &p, 10);
        int limit = (int) arg;
        srand (seed);
        cout << rand() % limit;
    }

    return 0;
}
