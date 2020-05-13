#include <iostream>
using namespace std;

void* build_name(char *name) {
    return (void*)name;
}

int main(int argc, char *argv[]) {
    void* (*p)(char*);
    //p = &build_name; // this works
    p = build_name; // this works
    char myword[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'A', 'd', 'r', 'i', 'a', 'n', 'u', 's', '!', '\0' };
    //void* a = (*p)(myword); // this works
    void* a = p(myword); // this works
    cout << (char*)a << endl;
    return 0;
}
