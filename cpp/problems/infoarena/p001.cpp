#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream in;
    ofstream out;
    in.open("in001.in");
    out.open("out001.out");
    int a, b;
    in >> a >> b;
    out << a + b;
    in.close();
    out.close();
    return 0;
}
