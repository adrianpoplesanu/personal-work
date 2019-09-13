#include<iostream>
using namespace std;

int x[10];

void init(int k) {
    x[k] = 1;
}

bool is_valid(int i, int n) {
    if (x[i] > n) return false;
    for(int k = 1; k < i; k++) {
        if (x[k] == x[i]) return false;
    }
    return true;
}

bool is_solution(int i, int n) {
    return i == n;
}

void next_value_vs_go_back(int &i, int n) {
    if (x[i] < n) x[i]++;
    else { i--; x[i]++; }
}

void print_solution(int n) {
    for(int i = 1; i <= n; i++) {
        cout<<x[i]<<" ";
    }
    cout<<endl;
}

void permutations(int n) {
    int i = 1;
    init(i);
    while(i > 0) {
        if(is_valid(i, n)) {
            if(is_solution(i, n)) {
                print_solution(n);
                next_value_vs_go_back(i, n);
            } else {
                i++;
                init(i);
            }
        } else {
            next_value_vs_go_back(i, n);
        }
    }
}

int main(int argc, char* argv[]) {
    int n = 4;
    permutations(n);
    return 0;
}
