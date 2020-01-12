#include <Foundation/Foundation.h>

@interface Starship : NSObject {
    NSString *name;
}
- (NSString*) OpenHailingFrequency : (NSString*) hello;
- (NSString*) GetStarshipName;
@end

@implementation Starship
- (id) init {
    self = [super init];
    return self;
}
- (id) init : (NSString*) _name {
    self = [super init];
    self->name = _name;
    return self;
}
- (NSString*) OpenHailingFrequency : (NSString*) hello {
    NSLog(@"Captain, we received this string: %@", hello);
    NSString *response = @"Opening hailing frequencies for Klingons";
    return response;
}
- (NSString*) GetStarshipName {
    NSString *_name = name;
    return _name;
}
@end

int main(int argc, char *argv[]) {
    NSLog(@"running...");
    //Starship *starship = [[Starship alloc] init];
    Starship *starship = [[Starship alloc] init : @"USS Enterprise"];
    NSString *response = [starship OpenHailingFrequency : @"welcome hoomans!"];
    NSLog(@"%@", response);
    NSString *name = [starship GetStarshipName];
    NSLog(@"%@", name);
    return 0;
}
