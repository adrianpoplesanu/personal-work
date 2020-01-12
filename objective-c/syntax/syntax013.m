#include <Foundation/Foundation.h>

@interface Interpreter : NSObject {
    @public
    NSString *command;
}
- (void) PrintCommand;
@end

@implementation Interpreter
- (id)init {
    self = [super init];
    return self;
}
- (void) PrintCommand {
    NSLog(@"%@", command);
}
@end

int main(int argc, char *argv[]) {
    NSLog(@"running...");
    Interpreter *interpreter = [[Interpreter alloc] init];
    interpreter->command = @"buna dimineata!";
    [interpreter PrintCommand];
    return 0;
}
