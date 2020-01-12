#include <Foundation/Foundation.h>

@interface Server : NSObject {
    @public
    NSString *welcome;
    @private
    int port;
    NSString *name;
}
- (void) SetName : (NSString*) new_name;
- (void) SetPort : (int) new_port;
- (void) PrintServerInfo;
- (void) SetInfo : (NSString*) new_name andPort : (int) new_part;
@end

@implementation Server
- (id)init {
    NSLog(@"in Server constructor");
    self = [super init];
    //welcome = @"Neata neata!";
    return self;
}
- (void) SetName:(NSString*) new_name {
    name = new_name;
}
- (void) SetPort:(int) new_port {
    port = new_port;
}
- (void) PrintServerInfo {
    NSLog(@"%@:%i says: %@", name, port, welcome);
}
- (void) SetInfo : (NSString*) new_name andPort : (int) new_port {
    name = new_name;
    port = new_port;
}
@end

int main(int argc, char *argv[]) {
    NSLog(@"running...");
    Server *server = [[Server alloc] init];
    [server SetPort : 8080];
    [server SetName : @"Apake Tumcat"];
    server->welcome = @"ho ho ho";
    [server PrintServerInfo];
    [server SetInfo : @"Glusfish Endecu" andPort : 9090];
    server->welcome = @"neata neata!";
    [server PrintServerInfo];
    return 0;
}
