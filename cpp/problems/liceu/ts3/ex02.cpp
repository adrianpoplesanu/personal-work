// BF & DF, graph, dynamic allocation graphs, adjacency list

#include <iostream>
#include <fstream>
#include <vector>

template<typename T>
struct Node {
    T value;
    Node<T>* next;
};

template<typename T>
void plain_print(Node<T>** nodes, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << nodes[i]->value << " " ;
    }
    std::cout << "\n";
}

template<typename T>
void free_nodes(Node<T>** nodes) {
    delete[] nodes;
}

template<typename T>
void addEdge(Node<T>** &nodes, int n, int i, int j) {
    Node<T> *node1 = nodes[i - 1];
    Node<T> *node2 = nodes[j - 1];
    while (node1->next != 0x0) {
        node1 = node1->next;
    }
    Node<T> *new_node1 = new Node<T>();
    new_node1->value = j;
    new_node1->next = 0x0;
    node1->next = new_node1;

    while (node2->next != 0x0) {
        node2 = node2->next;
    }
    Node<T> *new_node2 = new Node<T>();
    new_node2->value = i;
    new_node2->next = 0x0;
    node2->next = new_node2;
}

int main(int argc, char* argv[]) {
    int n, m, a[100][100], viz[100];
    std::ifstream in("ex02.in");
    in >> n >> m;

    Node<int>** nodes = new Node<int>*[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node<int>();
        nodes[i]->value = i;
    }

    for (int i = 0; i < m; i++) {
        int j, k;
        in >> j >> k;
        addEdge<int>(nodes, n, j, k);
    }

    plain_print(nodes, n);
    free_nodes(nodes);
    return 0;
}
