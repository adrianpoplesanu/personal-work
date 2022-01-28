#include <iostream>

int min(int heap[100], int size) {
    if (size > 0) {
        return heap[0];
    }
    return 0;
}

int removeMin(int heap[100], int &size) {
    int min = heap[0];
    int poz = 0;
    //size--;
    while(poz < size) {
        int temp, next;
        bool has_children = false;
        if (poz * 2 + 1 < size) {
            temp = heap[poz * 2 + 1];
            next = poz * 2 + 1;
            has_children = true;
        }
        if (poz * 2 + 2 < size) {
            temp = heap[poz * 2 + 2];
            next = poz * 2 + 2;
            has_children = true;
        }
        if (has_children) { // this is wrong
            heap[poz] = temp;
            poz = next;
        } else {
            break;
        }
    }
    size--;
    return min;
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
            std::cout << min(heap, size) << "\n";
        } else if (command == "remove") {
            int result = removeMin(heap, size);
            std::cout << result << "\n";
        } else if (command == "exit") {
            break;
        }
    }
    return 0;
}
