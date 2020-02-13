#include <Foundation/Foundation.h>

void change_name(NSString **violinist) {
    *violinist = @"Eddy";
    NSLog(@"%@", *violinist);
}

int main(int argc, char *argv[]) {
    NSString *violinist = @"Brett";
    NSLog(@"%@", violinist);
    change_name(&violinist);
    NSLog(@"%@", violinist);
    return 0;
}
