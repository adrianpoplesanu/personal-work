#include <iostream>

int random(int min, int max) {
   static bool first = true;
   if (first) {
      srand( time(NULL) );
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

int main(int argc, char* argv[]) {
    int n = 100;
    for (int i = 0; i < n; i++) {
        std::cout << random(0, 9);
        if (i != n - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}