#include <iostream>

using namespace std;

int st[10], n, k;

void Init() {
    st[k] = 0;
}

int Am_Succesor() {
    if (st[k] < n) {
        st[k]++;
        return 1;
    }
    return 0;
}

int E_Valid() {
    for (int i = 1; i < k; i++)
        if (st[i] == st[k]) return 0;
    return 1;
}

int Solutie() {
    return k == n;
}

void Tipar() {
    for (int i = 0; i < n; i++) cout<<st[i]<<" ";
    cout<<endl;
}

void back() {
    int AS;
    k = 1; Init();
    while (k > 0) {
        do { } while ((AS=Am_Succesor()) && !E_Valid());
        if (AS) {
            if (Solutie()) Tipar();
            else { k++; Init(); }
        } else k--; 
    }
}

int main() {
    cout<<"n = "; cin>>n;
    back();
    return 0;
}
