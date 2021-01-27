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
    cout << "original seed " << output << '\n';
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
    cout << "5 digit number seed " << output.substr(output.length() - 5) << '\n';
    string remainder = output.substr(output.length() - 5);
    int num = stoi(remainder);
    cout << num << '\n';
    return 0;
}
