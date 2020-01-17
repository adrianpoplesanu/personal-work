#include <Foundation/Foundation.h>

@interface PowerPlant : NSObject {
    @public
    int megawatts;
}
- (void) IncreaseMegaWatts : (int) value;
- (NSString*) ShowMegaWatts;
@end

@implementation PowerPlant
- (id) init {
    self = [super init];
    megawatts = 0;
    return self;
}
- (void) IncreaseMegaWatts : (int) value {
    megawatts += value;
}
- (NSString*) ShowMegaWatts {
    NSString *info;
    info = [NSString stringWithFormat:@"The powerplant generates %d Mwh", megawatts];
    return info;
}
@end

@interface NuclearPowerPlant : PowerPlant {

}
@end

@implementation NuclearPowerPlant
- (id) init {
    self = [super init];
    return self;
}
@end

@interface RBMK : NuclearPowerPlant {

}
@end

@implementation RBMK
- (id) init {
    self = [super init];
    return self;
}
@end

@interface Cernobyl : RBMK {

}
@end

@implementation Cernobyl
- (id) init {
    self = [super init];
    return self;
}
@end

int main(int argc, char *argv[]) {
    NSLog(@"running powerplants...");
    PowerPlant *powerplant = [[PowerPlant alloc] init];
    NSString *message;
    message = [powerplant ShowMegaWatts];
    NSLog(@"%@", message);
    [powerplant IncreaseMegaWatts : 700];
    message = [powerplant ShowMegaWatts];
    NSLog(@"%@", message);
    return 0;
}
