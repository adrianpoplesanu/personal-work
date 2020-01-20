#include <Foundation/Foundation.h>
#include "powerplant.h"

int main(int argc, char *argv[]) {
    NSLog(@"running nuclear powerplant simulation...");
    PowerPlant *powerplant = [[PowerPlant alloc] init];
    powerplant.name = @"Centrala Nucleara de la Cernavoda";
    [powerplant LogName];
    int reactor_num = [powerplant GetNumberOfReactors];
    NSLog(@"%d", reactor_num);
    return 0;
}
