// ts2 p25 e1
#include <iostream>
using namespace std;

struct student {
    int id;
    char name[40];
};

student build_data(int id, char name[40]) {
    student s;
    s.id = id;
    strcpy(s.name, name);
    return s;
}

void print_data(student s) {
    cout << s.id << " " << s.name << "\n";
}

int main (int argc, char *argv[]) {
    char a[40] = {'S', 'c', 'o', 'r', 'i', 'l', 'l', 'o'};
    student s = build_data(1, a);
    print_data (s);
    return 0;
}
