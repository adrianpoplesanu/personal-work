/*
   exercise: 074
   page: 428
   description: huffman codes
   command: echo 6 a 45 b 13 c 12 d 16 e 9 f 5 | ./program074
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

#define PARENT(i)       ((i) >> 1)
#define LEFT(i)         ((i) << 1)
#define RIGHT(i)        (((i) << 1) + 1)

struct Node {
    int frequency;
    char character;
    Node *left;
    Node *right;
};

Node *createNode(int frequency, char character) {
    Node *node = new Node();
    node->frequency = frequency;
    node->character = character;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void min_heapify(Node *q[], int n, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int smallest;
    if (l <= n && q[l]->frequency < q[i]->frequency) {
        smallest = l;
    } else {
        smallest = i;
    }
    if (r <= n && q[r]->frequency < q[smallest]->frequency) {
        smallest = r;
    }
    if (smallest != i) {
        Node *tmp = q[i];
        q[i] = q[smallest];
        q[smallest] = tmp;
        min_heapify(q, n, smallest);
    }
}

void build_min_heap(Node *q[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        min_heapify(q, n, i);
    }
}

Node *extract_min(Node *q[], int &n) {
    Node *min = q[1];
    q[1] = q[n];
    n--;
    if (n > 0) {
        min_heapify(q, n, 1);
    }
    return min;
}

void insert(Node *q[], int &n, Node *node) {
    n++;
    int i = n;
    q[i] = node;
    while (i > 1 && q[PARENT(i)]->frequency > q[i]->frequency) {
        Node *tmp = q[i];
        q[i] = q[PARENT(i)];
        q[PARENT(i)] = tmp;
        i = PARENT(i);
    }
}

// CLRS HUFFMAN(C): repeatedly merge the two least frequent trees.
Node *huffman(Node *q[], int n) {
    int size = n;
    for (int i = 1; i <= n - 1; i++) {
        Node *x = extract_min(q, size);
        Node *y = extract_min(q, size);
        Node *z = createNode(x->frequency + y->frequency, '\0');
        z->left = x;
        z->right = y;
        insert(q, size, z);
    }
    return extract_min(q, size);
}

void print_codes(Node *node, char code[], int depth) {
    if (node->left == nullptr && node->right == nullptr) {
        if (depth == 0) {
            std::cout << node->character << " 0\n";
            return;
        }
        code[depth] = '\0';
        std::cout << node->character << " " << code << "\n";
        return;
    }
    code[depth] = '0';
    print_codes(node->left, code, depth + 1);
    code[depth] = '1';
    print_codes(node->right, code, depth + 1);
}

void free_tree(Node *node) {
    if (node == nullptr) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    delete node;
}

void read(Node *q[], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        char character;
        int frequency;
        std::cin >> character >> frequency;
        q[i] = createNode(frequency, character);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    Node *q[50];
    int n;
    read(q, n);
    build_min_heap(q, n);

    Node *root = huffman(q, n);
    char code[50];
    print_codes(root, code, 0);
    free_tree(root);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
