#include <Foundation/Foundation.h>

int main(int argc, char *argv[]) {
    NSLog(@"running a curl test in objective-c");
    NSURL *url = [NSURL URLWithString:@"https://cursvalutar.ro"];
    NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:url];
    [req setHTTPMethod:@"GET"];

    NSData *res = [NSURLConnection sendSynchronousRequest:req returningResponse:NULL error:NULL];
    NSString *myString = [[NSString alloc] initWithData:res encoding:NSUTF8StringEncoding];
    NSLog(@"%@", myString);

    return 0;
}
