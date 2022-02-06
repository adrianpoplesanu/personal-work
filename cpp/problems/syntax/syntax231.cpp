#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

int main(int argc, char* argv[]) {
    std::string text = "adrian";
    int textLen = 6, k = 0;
    int show[10], count[10], maxChanges = 2;
    for (int i = 0; i < 10; i++) show[i] = count[i] = 0;
    while(1) {
        for (int i = 0; i < 10; i++) {
            if (show[i] == 1) {
                if (k >= textLen) {
                    k = 0;
                }
                std::cout << text[k++] << " ";
            } else {
                std::cout << "  ";
            }
            count[i]++;
        }
        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        for (int j = 0; j < maxChanges; j++) {
            int col = rand() % 10;
            if (count[col] > 6) {
                if (show[col] == 1) show[col] = 0;
                else show[col] = 1;
                count[col] = 0;
            }
        }
    }
    return 0;
}
