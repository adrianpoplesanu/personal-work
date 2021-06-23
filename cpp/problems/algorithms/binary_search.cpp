#include<iostream>

bool binary_search(int a[10], int target, int low, int high) {
    int mid = (low + high)/2;
    if (low > high) return false;
    if (target==a[mid]) return true;
    if (target < a[mid]) {
        return binary_search(a, target, low, mid - 1);
    } else {
        return binary_search(a, target, mid + 1, high);
    }
}

int main(int argc, char *argv[]) {
    int a[] = {1, 2, 3, 5, 6, 8, 9};
    for (int i = 0; i < 7; i++) std::cout << a[i] << " ";
    std::cout << "\n";
    std::cout << "2: " << binary_search(a, 2, 0, 6) << "\n";
    std::cout << "4: " << binary_search(a, 4, 0, 6) << "\n";
    std::cout << "1: " << binary_search(a, 1, 0, 6) << "\n";
    std::cout << "7: " << binary_search(a, 7, 0, 6) << "\n";
    std::cout << "9: " << binary_search(a, 9, 0, 6) << "\n";
    return 0;
}
