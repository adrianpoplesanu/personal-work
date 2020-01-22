#include <Foundation/Foundation.h>

@interface City : NSObject
@property (nonatomic, assign) NSString *name;
@end

@implementation City

@end

int main(int argc, char *argv[]) {
    City *cities[3];
    for (int i = 0; i < 3; i++) {
        cities[i] = [[City alloc] init];
        cities[i].name = @"Budapest";
    }
    NSArray *array = [NSArray arrayWithObjects:cities count:3];
    NSLog(@"%@", array);
    return 0;
}
