#include <iostream>
using namespace std;

struct Box {
    int num;
    int mem_fragments;
    int mem_fragment_size;
};

struct Box2 {
    int num;
    int mem_fragments;
    int mem_fragment_size;
    string name;
};

int main(int argc, char *argv[]) {
    cout << "sizeof(Box) = " << sizeof(Box) << "\n";
    cout << "sizeof(Box2) = " << sizeof(Box2) << "\n";
    Box aws_box0;
    cout << "sizeof(aws_box0) = " << sizeof(aws_box0) << "\n";
    Box2 aws_box1;
    aws_box1.name = "North Virginia, east1, region1";
    cout << "sizeof(aws_box1) = " << sizeof(aws_box1) << "\n";
    cout << "sizeof(aws_box1.name) = " << sizeof(aws_box1.name) << "\n";
    Box2 *aws_box2 = new Box2();
    aws_box2->name = "South Virginia, east2, region3";
    cout << "sizeof(aws_box2) = " << sizeof(aws_box2) << "\n";
    cout << "sizeof(aws_box2->name) = " << sizeof(aws_box2->name) << "\n";
    return 0;
}
