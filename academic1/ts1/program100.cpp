/*
   exercise: 100
   description: place vowels before consonants
   command: echo 8 b a c E d i o f | ./program100
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

bool isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
           ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
}

void placeVowelsBeforeConsonants(char a[], int n) {
    char result[50];
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (isVowel(a[i])) {
            result[k++] = a[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (!isVowel(a[i])) {
            result[k++] = a[i];
        }
    }
    for (int i = 0; i < n; i++) {
        a[i] = result[i];
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    char a[50];
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    placeVowelsBeforeConsonants(a, n);

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
