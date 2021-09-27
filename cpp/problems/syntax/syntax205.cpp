#include <iostream>

int main(int argc, char *argv[]) {
    char c;
    // Set the terminal to raw mode
    std::cout << "Press . to quit\n";
    system("stty raw");
    int up_arrow = 0;
    while(1) {
        //system("stty raw");
        c = getchar();
        //system("stty cooked");
        // terminate when "." is pressed
        if (up_arrow == 0 && (int)c == 27) {
            up_arrow++;
        } else
        if (up_arrow == 1 && (int)c == 91) {
            up_arrow++;
        } else
        if (up_arrow == 2 && (int)c == 65) {
            std::cout << "up arrow pressed";
        } else {
            up_arrow = 0;
        }
        //std::cout << (int)c;
        if(c == '.') {
            system("stty cooked");
            exit(0);
        }  
        if (up_arrow == 0) {
            if ((int)c == 13) std::cout << "\n";
            else std::cout << c;
        }
    }
    return 0;
}
