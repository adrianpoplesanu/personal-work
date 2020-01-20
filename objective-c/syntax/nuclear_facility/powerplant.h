#include <Foundation/Foundation.h>
#include "reactor.h"

@interface PowerPlant : NSObject {
    //@private;
    //Reactor[] reactors;
    //int reactor_numbers;
}
@property (assign) int reactorNumbers;
@property (assign) NSString *name;
@property (assign) NSString *address;
- (void) LogName;
@end
