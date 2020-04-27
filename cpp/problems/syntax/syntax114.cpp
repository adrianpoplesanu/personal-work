// fun with function pointers
#include<iostream>
using namespace std;

void print_num(int a) {
    cout << a << endl;
}

void* add_num(int *a, int *b) {
    int *c;
    c = new int();
    *c = *a + *b;
    //*c = 12;
    return c;
}

void fun() {
    // not working
    //void (*(*f[])())();
    // it should do this
    // defines f as an array of unspecified size, of pointers to functions that return pointers to functions that return void
}

int main(int argc, char *argv[]) {
    void (*f1)(int);

    f1 = print_num;
    f1(5);

    int *a, *b, *c;
    a = new int();
    *a = 5;
    b = new int();
    *b = 6;
    //c = (int*)add_num(a, b);
    //cout << c << " " << *c << endl;

    void *(*func)(int*, int*);
    func = add_num;
    c = (int*)func(a, b);
    cout << c << " " << *c << endl;

    return 0;
}
