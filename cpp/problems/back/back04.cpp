// http://info.mcip.ro/?cap=Backtracking #834
#include <iostream>
using namespace std;

void display(int a[], int heights[], int n) {
    cout << "============\n";
    for (int i = 0; i < n; i++) cout << heights[a[i]] << " ";
    cout << "\n";
    for (int i = n; i < 2 * n; i++) cout << heights[a[i]] << " ";
    cout << "\n";
}

bool accept(int a[], int heights[], int k, int n) {
    for (int i = 0; i < k; i++) if (a[i] == a[k]) return false;
    if (k == 0) return true;
    else {
        if (k < n) {
            if (heights[a[k - 1]] < heights[a[k]]) return false;
        } else {
            if (heights[a[k - n]] < heights[a[k]]) return false;
            if (k == n) return true;
            else {
                if (heights[a[k - 1]] < heights[a[k]]) return false;
            }
        }
    }
    return true;
}

void back(int a[], int heights[], int k, int n) {
    if (k == 2 * n) {
        display(a, heights, n);
    } else {
        a[k] = 0;
        while(a[k] < 2 * n) {
            if (accept(a, heights, k, n)) {
                back(a, heights, k + 1, n);
            }
            a[k]++;
        }
    }
}

int main(int argc, char *argv[]) {
    int n = 3;
    int heights[] = {183, 180, 169, 195, 193, 184};
    int a[2 * n];
    memset(a, 0, sizeof(a));

    back(a, heights, 0, n);
    return 0;
}