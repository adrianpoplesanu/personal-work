#include <iostream>

// [17:32:26] adrianpoplesanu:syntax git:(master*) $ ./syntax263 > ../../../python/syntax/color_output.py 
// [17:32:39] adrianpoplesanu:syntax git:(master*) $ python3 ../../../python/syntax/color_output.py 

int main(int argc, char *argv[]) {
    for (int i = 0; i < 100; i++) {
        std::cout << "print (\"" << i << " \\033[0;" << i << "mtest\\033[0m\")\n";
    }
    return 0;
}
