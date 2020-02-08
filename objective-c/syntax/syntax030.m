#include <Foundation/Foundation.h>

struct Neata {
    int id;
    char *greeting;
};

int main(int argc, char *argv[]) {
    struct Neata neata;
    neata.id = 110;
    neata.greeting = "buna dimineata!!!";
    NSLog(@"%s", neata.greeting);
    return 0;
}
