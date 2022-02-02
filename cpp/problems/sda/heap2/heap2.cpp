// i don't remember how i implemented it, so doing it again
#include <iostream>

void insert(int heap[100], int& size, int val) {
    heap[size++] = val;
    int poz = size - 1;
    while (poz > 0) {
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

int remove(int heap[100], int& size) {
    if (size == 0) {
        std::cout << "heap-ul e gol\n";
        return 0;
    }
    int result = heap[0];
    int poz = 0;
    while (poz < size) {
        bool has_children = false;
        int next, temp;
        if (poz * 2 + 1 < size) {
            has_children = true;
            temp = heap[poz * 2 + 1];
            next = poz * 2 + 1;
        }
        if (poz * 2 + 2 < size) {
            has_children = true;
            if (heap[poz * 2 + 2] < temp) {
                temp = heap[poz * 2 + 2];
                next = poz * 2 + 2;
            }
        }
        if (!has_children) {
            for (int i = poz; i < size; i++) heap[i] = heap[i + 1];
            break;
        }
        heap[poz] = temp;
        poz = next;
    }
    size--;
    return result;
}

void display(int heap[100], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << heap[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    int heap[100], size = 0;
    bool running = true;
    std::string command;
    int val;
    while(running) {
        std::cout << ">> ";
        std::cin >> command;
        if (command == "add") {
            std::cin >> val;
            insert(heap, size, val);
        }
        if (command == "remove") {
            val = remove(heap, size);
            std::cout << val << "\n";
        }
        if (command == "print") {
            display(heap, size);
        }
        if (command == "") std::cout <<"\n";
        if (command == "exit") running = false;
    }
    return 0;
}
