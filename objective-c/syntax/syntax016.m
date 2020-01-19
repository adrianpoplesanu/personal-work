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
@private
    int megawatts_per_unit;
    int maximum_allowed_megawatts;
}
@property (assign) int total_cores;
- (void) DisplayNumberOfCores;
- (void) ChangeMegawattsPerUnit : (int) value withMaximumAllowed : (int) maximum_allowed;
- (void) DisplayMegawattsOutput;
@end

@implementation NuclearPowerPlant
- (id) init {
    self = [super init];
    return self;
}
- (id) init : (int) total_cores_value {
    self = [super init];
    self.total_cores = total_cores_value;
    return self;
}
- (void) DisplayNumberOfCores {
    NSLog(@"%d", _total_cores);
}
- (void) ChangeMegawattsPerUnit : (int) value withMaximumAllowed : (int) maximum_allowed {
    megawatts_per_unit = value;
    maximum_allowed_megawatts = maximum_allowed;
}
- (void) DisplayMegawattsOutput {
    NSLog(@"%d Mwh [of maximum %d Mwh]", megawatts_per_unit, maximum_allowed_megawatts);
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
    NuclearPowerPlant *nuclearpowerplant = [[NuclearPowerPlant alloc] init];
    nuclearpowerplant.total_cores = 2;
    [nuclearpowerplant DisplayNumberOfCores];
    [nuclearpowerplant ChangeMegawattsPerUnit : 800 withMaximumAllowed : 3200];
    [nuclearpowerplant DisplayMegawattsOutput];
    NuclearPowerPlant *nuclearpowerplant2 = [[NuclearPowerPlant alloc] init : 3];
    [nuclearpowerplant2 DisplayNumberOfCores];
    return 0;
}
