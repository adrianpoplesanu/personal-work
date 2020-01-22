#include <Foundation/Foundation.h>

int main(int argc, char *argv[]) {
    NSString *names[3];
    names[0] = @"Belfast";
    names[1] = @"Copenhaga";
    names[2] = @"Dwashington";
    NSArray *cities = [NSArray arrayWithObjects : names count : 3];
    NSLog(@"%@", cities);
    return 0;
}
