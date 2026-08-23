/*
   exercise: 037
   page: 233
   description: stack implementation with array
   command: ./program037
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

bool stack_empty(int s[], int n) {
    if (n == 0) {
        return true;
    }
    return false;
}

void push(int s[], int &n, int x) {
    s[n] = x;
    n++;
}

int pop(int s[], int &n) {
    if (stack_empty(s, n)) {
        std::cout << "[ ERROR ] underflow";
        return 0;
    } else {
        n--;
        return s[n];
    }
}

void printStack(int s[], int n) {
    std::cout << "[ STACK ] ";
    for (int i = 0; i < n; i++) std::cout << s[i] << " ";
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int s[50], n = 0;

    std::cout << stack_empty(s, n);

    push(s, n, 11);
    push(s, n, 12);

    printStack(s, n);

    push(s, n, 44);

    printStack(s, n);

    int val = pop(s, n);
    std::cout << "[ VALUE ] " << val << "\n";
    val = pop(s, n);
    std::cout << "[ VALUE ] " << val << "\n";

    printStack(s, n);
    std::cout << stack_empty(s, n) << "\n";
    val = pop(s, n);
    std::cout << "[ VALUE ] " << val << "\n";
    std::cout << stack_empty(s, n) << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

