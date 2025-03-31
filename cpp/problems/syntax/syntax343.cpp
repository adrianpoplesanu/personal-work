// this doesn't work like i want
#include <iostream>

int main(int argc, char *argv[]) {
    std::string s;
    char *lineptr[100];
    int nlines = 0;
    while((std::cin >> s)) {
        std::cout << "[ OUT ] " << s.c_str() << "\n";
        lineptr[nlines] = (char*) s.c_str();
        nlines++;
    }
    int i = 0;
    while(i < nlines) {
        std::cout << "[ LOG ] " << i << " " << lineptr[i++] << "\n";
    }
    return 0;
}
