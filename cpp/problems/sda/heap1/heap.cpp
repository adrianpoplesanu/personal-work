#include <iostream>

int min() {
    return 0;
}

int removeMin(int heap[100], int &size) {
    return 0;
}

void insert(int heap[100], int &size, int e) {
    heap[size++] = e;
    int poz = size - 1;
    while(poz >= 0) {
        if (heap[poz / 2] > heap[poz]) {
            int aux = heap[poz];
            heap[poz] = heap[poz / 2];
            heap[poz / 2] = aux;
            poz = poz / 2;
        } else {
            break;
        }
    }    
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
        
        }
    }
    return 0;
}
