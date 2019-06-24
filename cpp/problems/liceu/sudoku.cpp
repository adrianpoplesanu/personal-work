#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout<<"Usage: ./sudoku sudoku.in sudoku.out"<<endl;
        return 1;
    }

    ifstream in(argv[1]);
    ofstream out(argv[2]);

    int tabla[9][9];
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            in>>tabla[i][j];
        }
    }

    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout<<tabla[i][j]<<" ";
        }
        cout<<endl;
    }

    in.close();
    out.close();

    return 0;
}