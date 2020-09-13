#include <iostream>
#include <vector>
using namespace std;

int main (int argc, char *argv[]) {
    vector<int> adj[10];
    
    for (int i = 0; i < 10; i++) {
        adj[i].push_back(5);
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < adj[i].size(); ++j) {
             cout << adj[i][j] << "\n";
        }
    }
    return 0;
}
