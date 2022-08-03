#include <iostream>

int main(int argc, char* argv[]) {
   int steps = 0;
   int n = 20;

   for (int i = 0; i < n; i++) {
       for (int j = i; j < n; j++) {
           for (int k = i; k <= j; k++) {
               steps += 1;
           }
       }
   }

   std::cout << n << "\n" << steps << "\n";
   return 0;
}
