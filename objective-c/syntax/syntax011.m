#include <Foundation/Foundation.h>

@interface Compiler : NSObject {
    @public
    NSString *text;
}
@property(nonatomic, readwrite) NSString *command;
- (void) PrintCommand;
@end

@implementation Compiler
- (void) PrintCommand {
    NSLog(@"in PrintCommand: %@", self.command);
}

-(id)init {
    self = [super init];
    text = @"buna dimineata!";
    return self;
}
@end

int main(int argc, char *argv[]) {
    NSLog(@"running...");
    Compiler *compiler = [[Compiler alloc] init];
    compiler.command = @"ls -la";
    compiler->text = @"buna seara prieteni! :))";
    [compiler PrintCommand];
    return 0;
}
