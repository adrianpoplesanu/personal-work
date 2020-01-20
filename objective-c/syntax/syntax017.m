#include <Foundation/Foundation.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main(int argc, char *argv[]) {
    NSLog(@"running...");
    NSLog(@"%d", max(5, 7));
    NSLog(@"%d", max(2, 5));
    NSLog(@"%d", max(9, 3));
    return 0;
}
