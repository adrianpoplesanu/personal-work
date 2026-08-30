/*
   exercise: 042
   page: 235
   description: implement two stacks using a single array
   command: ./program042
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

enum StackType {
    STACK_LEFT,
    STACK_RIGHT,
};

struct Stack {
    int top;
    StackType type;
};

void initialize_stack(Stack &stack, StackType type, int n) {
    stack.type = type;
    if (type == STACK_LEFT) {
        stack.top = 0;
    } else {
        stack.top = n - 1;
    }
}

void push(Stack &stack, int a[], int x) {
    if (stack.type == STACK_LEFT) {
        a[stack.top] = x;
        stack.top++;
    } else {
        a[stack.top] = x;
        stack.top--;
    }
}

int pop(Stack &stack, int a[]) {
    if (stack.type == STACK_LEFT) {
        stack.top--;
        int value = a[stack.top];
        a[stack.top] = 0;
        return value;
    }
    else {
        stack.top++;
        int value = a[stack.top];
        a[stack.top] = 0;
        return value;
    }
}

void print_stack(Stack &stack, int a[], int n) {
    if (stack.type == STACK_LEFT) {
        std::cout << "Stack: ";
        for (int i = stack.top - 1; i >= 0; i--) {
            std::cout << a[i] << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Stack: ";
        for (int i = stack.top + 1; i < n; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << "\n";
    }
}

void initialize_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
}

void print_array(int a[], int n) {
    std::cout << "Array: ";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n = 50;

    initialize_array(a, n);

    Stack stack_left;
    initialize_stack(stack_left, STACK_LEFT, n);
    Stack stack_right;
    initialize_stack(stack_right, STACK_RIGHT, n);

    push(stack_left, a, 1);
    push(stack_left, a, 2);
    push(stack_left, a, 3);
    push(stack_right, a, 4);
    push(stack_right, a, 5);
    push(stack_right, a, 6);

    print_stack(stack_left, a, n);
    print_stack(stack_right, a, n);

    print_array(a, n);

    std::cout << "Pop from left stack: " << pop(stack_left, a) << "\n";
    std::cout << "Pop from right stack: " << pop(stack_right, a) << "\n";

    print_stack(stack_left, a, n);
    print_stack(stack_right, a, n);

    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

