#include <Foundation/Foundation.h>

@implementation Reactor
- (void) IncreaseOutput : (int) step {
    self.current_mwh += step;
}
@end
