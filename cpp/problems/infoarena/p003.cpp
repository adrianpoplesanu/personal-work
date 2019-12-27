#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void decToBinary(int n, int cifre) { 
    int binaryNum[64]; 
  
    int i = 0; 
    while (n > 0) { 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    }
    for (int j = cifre - 1; j >= i; j--) binaryNum[j] = 0;
 
    //for (int j = cifre - 1; j >= 0; j--) 
    //    out << binaryNum[j]; 
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    ifstream in;
    ofstream out;
    in.open("in003.in");
    out.open("out003.out");
   
    int n, m;
    in >> n >> m;
    int a[n][m];
    //for (int i = 0; i < n; i++) 
    //    for (int j = 0; j < m; j++) in >> a[i][j];
    
    cout << (1 << (n + m - 1)) << endl;
    for (int i = 0; i < (1 << (n + m)); i++) {
        decToBinary(i, n + m); out << endl;
    }
 
    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}
