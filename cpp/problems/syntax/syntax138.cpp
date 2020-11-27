#include <fstream>
using namespace std;

int main (int argc, char *argv[]) {
    ofstream out("syntax139.cpp");
    out << "#include <iostream>" << "\n";
    out << "using namespace std;" << "\n";
    out << "int main() {" << "\n";
    for (int i = 0; i < 10000; i++) {
        out << "    int a"<<i<<" = " << i << ";\n";
    }
    out << "}" << "\n";
    return 0;
}
