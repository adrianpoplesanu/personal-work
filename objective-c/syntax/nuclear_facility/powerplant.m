#import <Foundation/Foundation.h>
#import "powerplant.h"

@implementation PowerPlant
- (id) init {
    self = [super init];
    total_reactors = 0;
    return self;
}
- (void) LogName {
    NSLog(@"Name: %@", _name);
}
- (int) GetNumberOfReactors {
    return total_reactors;   
}
@end
