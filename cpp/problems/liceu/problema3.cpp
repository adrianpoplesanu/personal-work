#include <iostream>
#include <exception>

using namespace std;

void init(int &item) {
    item = 0;
}

bool Am_Succesor(int heap[10], int k, int n) {
    if (heap[k] < n) {
        heap[k]++;
        return true;
    }
    return false;
}

bool E_Valid(int heap[10], int k) {
    for (int i = 1; i < k; i++) {
        if (heap[i] == heap[k]) return false;
    }
    return true;
}

bool Solutie(int k, int n) {
    return k == n;
}

void Tipar(int heap[10], int n) {
    for (int i = 1; i <= n; i++) cout<<heap[i]<<" ";
    cout<<endl;
}

void back(int n) {
    bool AS;
    int heap[10], k = 1;
    init(heap[k]);
    while (k > 0) {
        do { } while ((AS = Am_Succesor(heap, k, n)) && !E_Valid(heap, k));
        if (AS) {
            if (Solutie(k, n)) Tipar(heap, n);
            else { k++; init(heap[k]); }
        } else {
            k--;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout<<"Usage: ./problema2 5"<<endl;
        return 1;
    }

    int n;
    try {
        n = stoi(argv[1]);
    } catch(exception e) {
        cout<<"The param needs to be an int. Caught exception: "<<e.what()<<endl;
    }

    back(n);
    return 0;
}
