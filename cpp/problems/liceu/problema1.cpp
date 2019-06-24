#include <iostream>
#include <exception>

using namespace std;

int next(int current) {
    if (current == 9) return 1;
    return current + 1;
}

void solve(int n, int m) {
    int current = n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= i; j++) {
            cout<<current<<" ";
            current = next(current);
        }
        cout<<endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout<<"Usage: ./problema1 m n"<<endl;
        return 1;
    }
        
    int n, m;
    try {
        m = stoi(argv[1]);
        n = stoi(argv[2]);
    } catch(exception& e) {
        cout<<"Both params need to be int. Caught exeption: "<<e.what()<<endl;
    }

    solve(n, m);

    return 0;
}
