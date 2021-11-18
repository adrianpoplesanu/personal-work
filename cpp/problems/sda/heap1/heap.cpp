#include <iostream>

int min(int heap[100], int size) {
    if (size > 0) {
        return heap[size - 1];
    }
    return 0;
}

int removeMin(int heap[100], int &size) {
    return 0;
}

void insert(int heap[100], int &size, int e) {
    heap[size++] = e;
    int poz = size - 1;
    while(poz > 0) {
        if (heap[(poz - 1) / 2] > heap[poz]) {
            int aux = heap[poz];
            heap[poz] = heap[(poz - 1) / 2];
            heap[(poz - 1) / 2] = aux;
            poz = (poz - 1) / 2;
        } else {
            break;
        }
    }    
}

void print(int heap[100], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << heap[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    std::cout << "running heap test...\n";
    int heap[100], size = 0;
    while(1) {
        std::string command;
        std::cout << ">> ";
        std::cin >> command;
        if (command == "add") {
            int var;
            std::cin >> var;
            insert(heap, size, var);
        } else if (command == "print") {
            print(heap, size);
        } else if (command == "min") {
            std::cout << min(heap, size);
        } else if (command == "remove") {

        } else if (command == "exit") {
            break;
        }
    }
    return 0;
}
