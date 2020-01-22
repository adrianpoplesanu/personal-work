#include <Foundation/Foundation.h>

@interface Engine : NSObject {
    @private
    int warp_factor;
}
@end

@implementation Engine

@end

@interface Starship : NSObject {
    @public
    //Engine *engine[];
}
@end

@implementation Starship

@end

int main(int argc, char *argv[]) {
    Starship *starship = [[Starship alloc] init];
    return 0;
}
