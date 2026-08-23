/*
   exercise: 038
   page: 235
   description: queue implementation with array
   command: ./program038
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void enqueue(int q[], int n, int &head, int &tail, int x) {
    q[tail] = x;
    if (tail == n - 1) {
        tail = 0;
    } else {
        tail++;
    }
}

int dequeue(int q[], int n, int &head, int &tail) {
    int x = q[head];
    if (head == n - 1) {
        head = 0;
    } else {
        head++;
    }
    return x;
}

void printQueue(int q[], int n, int head, int tail) {
    std::cout << "[ QUEUE ] ";
    while (head != tail) {
        std::cout << q[head] << " ";
        head++;
        if (head == n) {
            head = 0;
        }
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int q[50], n = 50, head = 0, tail = 0;

    printQueue(q, n, head, tail);


    enqueue(q, n, head, tail, 11);
    enqueue(q, n, head, tail, 27);
    enqueue(q, n, head, tail, 34);

    printQueue(q, n, head, tail);

    int val = dequeue(q, n, head, tail);
    std::cout << "[ VALUE ] " << val << "\n";

    printQueue(q, n, head, tail);

    val = dequeue(q, n, head, tail);
    std::cout << "[ VALUE ] " << val << "\n";

    val = dequeue(q, n, head, tail);
    std::cout << "[ VALUE ] " << val << "\n";

    printQueue(q, n, head, tail);

    for (int i = 0; i < 49; i++) {
        enqueue(q, n, head, tail, i);
    }

    printQueue(q, n, head, tail);
    std::cout << "[ HEAD ] " << head << "\n";
    std::cout << "[ TAIL ] " << tail << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

