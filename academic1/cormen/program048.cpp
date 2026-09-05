/*
   exercise: 048
   page: 271
   description: hash-insert under open addressing
   command: ./program048
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0
#define NIL -1

int h_prime(int k, int m) {
    return k % m;
}

int h(int k, int i, int m) {
    return (h_prime(k, m) + i) % m;
}

int hash_insert(int T[], int m, int k) {
    int i = 0;
    do {
        int j = h(k, i, m);
        if (T[j] == NIL) {
            T[j] = k;
            return j;
        } else {
            i = i + 1;
        }
    } while (i != m);
    std::cout << "[ ERROR ] hash table overflow\n";
    return -1;
}

int hash_search(int T[], int m, int k) {
    int i = 0;
    int j;
    do {
        j = h(k, i, m);
        if (T[j] == k) {
            return j;
        }
        i++;
    } while(i != m && T[j] != NIL);
    return NIL;
}

void print_table(int T[], int m) {
    std::cout << "[ TABLE ] ";
    for (int i = 0; i < m; i++) {
        if (T[i] == NIL) {
            std::cout << "NIL ";
        } else {
            std::cout << T[i] << " ";
        }
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int m = 11;
    int T[11];
    for (int i = 0; i < m; i++) {
        T[i] = NIL;
    }

    print_table(T, m);

    int keys[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    int n = 9;
    for (int i = 0; i < n; i++) {
        int slot = hash_insert(T, m, keys[i]);
        std::cout << "[ INSERT ] " << keys[i] << " -> slot " << slot << "\n";
    }

    print_table(T, m);

    hash_insert(T, m, 1);
    hash_insert(T, m, 2);
    print_table(T, m);

    hash_insert(T, m, 3);

    int search_key = 17;
    int slot1 = hash_search(T, m, search_key);
    if (slot1 != NIL) {
        std::cout << "[ SEARCH ] " << search_key << " -> slot " << slot1 << "\n";
    } else {
        std::cout << "[ SEARCH ] " << search_key << " not found\n";
    }

    int slot2 = hash_search(T, m, 100);
    if (slot2 != NIL) {
        std::cout << "[ SEARCH ] " << 100 << " -> slot " << slot2 << "\n";
    } else {
        std::cout << "[ SEARCH ] " << 100 << " not found\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
