#include <Foundation/Foundation.h>

void execute(NSString *command) {
    NSLog(@"%@", command);
}

int main(int argc, char *argv[]) {
    NSString *command = @"php_eval :)";
    execute(command);
    return 0;
}
