// ts2 p39 e1
#include <iostream>
using namespace std;

int calculate_digit_cubes(int n) {
    int sum = 0, r;
    while (n != 0) {
        r = n % 10;
        sum += r * r * r;
        n /= 10;
    }
    return sum;
}

bool number_found(int visited[1000], int size, int n) {
    for (int i = 0 ; i < size; i++) {
        if (visited[i] == n) return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    int n, visited[1000], i = 0;
    cout << "n = "; cin >> n;
    while(!number_found(visited, i, n)) {
        visited[i] = n;
        ++i;
        n = calculate_digit_cubes(n);
    }
    visited[i] = n;
    ++i;
    for (int j = 0; j < i; ++j) {
        cout << visited[j] << " ";
    }
    cout << "\n";
    return 0;
}
