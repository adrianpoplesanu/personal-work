// BF & DF, graph, adjacency matrix

#include <iostream>
#include <fstream>

void print_adjacency_matrix(int n, int a[100][100]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << '\n';
    }
}

void bf(int n, int a[100][100], int k, int viz[100]) {
    int queue[100], p, u;
    p = 0;
    u = 1;
    queue[0] = k;
    viz[k] = 1;
    while(p < u) {
        int k = queue[p++];
        std::cout << k << " ";
        for (int i = 0; i < n; i++) {
            if (a[k][i] && !viz[i]) {
                queue[u++] = i;
                viz[i] = 1;
            }
        }
    }
}

void df(int n, int a[100][100], int k, int viz[100]) {
    std::cout << k << " ";
    viz[k] = 1;
    for (int i = 0; i < n; i++) {
       if (a[k][i] && !viz[i]) {
           df(n, a, i, viz);
       } 
    }
}

int main(int argc, char* argv[]) {
    int n, m, a[100][100], viz[100];
    std::ifstream in("ex01.in");
    in >> n >> m;
    for (int i = 0; i < m; i++) {
        int j, k;
        in >> j >> k;
        a[j - 1][k - 1] = a[k - 1][j - 1] = 1;
    }
    in.close();

    //print_adjacency_matrix(n, a);
    memset(viz, 0, sizeof(viz));
    bf(n, a, 0, viz);
    std::cout << "\n";
    memset(viz, 0, sizeof(viz));
    df(n, a, 0, viz);
    std::cout << "\n";
    return 0;
}
