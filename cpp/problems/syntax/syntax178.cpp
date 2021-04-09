#include <iostream>

// replaced PyObject with int

static void reverse_slice(int **lo, int **hi) {
    //assert(lo && hi); // i need a macro for this

    --hi;
    while (lo < hi) {
        int *t = *lo;
        *lo = *hi;
        *hi = t;
        ++lo;
        --hi;
    }
}

int main(int argc, char *argv[]) {
    return 0;
}
