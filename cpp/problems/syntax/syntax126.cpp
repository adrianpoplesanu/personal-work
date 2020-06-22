#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    ofstream out("funny2.cpp");

    out << "#include <iostream>" << endl << "using namespace std;" << endl << endl << "int main() {" << endl;
    for (int i = 0; i < 4096; i++) {
        out << "    int variabila" << i << " = " << i << ";" << endl;
    }
    out << "    return 0;" << endl << "}";

    out.close();
    return 0;
}
