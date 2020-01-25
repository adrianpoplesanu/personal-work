#include <Foundation/Foundation.h>
#include "reactor.h"

@interface PowerPlant : NSObject {
    @private;
    Reactor *reactor[5]; // this needs to be an array
    int total_reactors;
}
@property (assign) int reactorNumbers;
@property (assign) NSString *name;
@property (assign) NSString *address;
- (void) LogName;
- (int) GetNumberOfReactors;
@end
