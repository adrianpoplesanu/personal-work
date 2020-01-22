#import <Foundation/Foundation.h>

@interface Reactor : NSObject {

}
@property (assign) int max_mwh;
@property (assign) int current_mwh;
- (void) IncreaseOutput : (int) step;
@end
