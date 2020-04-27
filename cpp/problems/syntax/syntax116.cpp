#include <iostream>
using namespace std;

int print() {
    return 7;
}

int (*provider()) () {
    return print;
}

int main(int argc, char *argv[]) {
    //int (*f()());
    //f = provider;
    //void *f;
    //f = (int (*()))provider;

    // trying to do a pointer to a pointer function... not working

    //cout << typeof(*provider) << endl;
    cout << provider() << endl;
    cout << provider()() << endl;
    return 0;
}
