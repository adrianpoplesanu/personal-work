#include <Foundation/Foundation.h>

void practice_40hours(NSString *violinists[3]) {
    violinists[0] = @"Ling Ling";
    violinists[1] = @"Ling Ling";
    violinists[2] = @"Ling Ling";
}

int main(int argc, char *argv[]) {
    NSString *violinists[3];
    violinists[0] = @"Eddie Chen";
    violinists[1] = @"Brett Yang";
    violinists[2] = @"Hillaty Hahn";
    NSLog(@"before practicing...");
    for (int i = 0; i < 3; i++) NSLog(@"%@", violinists[i]);
    practice_40hours(violinists);
    NSLog(@"after practicing...");
    for (int i = 0; i < 3; i++) NSLog(@"%@", violinists[i]);
    return 0;
}
