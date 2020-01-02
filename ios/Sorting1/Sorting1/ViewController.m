//
//  ViewController.m
//  Sorting1
//
//  Created by Adrian Poplesanu on 12/28/19.
//  Copyright © 2019 Adrian Poplesanu. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)SortButtonClicked:(id)sender {
    NSLog(@"Hello World!");
    //NSLog(@"%@", _InputField.text);
    NSString *data = _InputField.text;
    NSLog(@"%lu", (unsigned long)data.length);
    //printf("%s", _InputField.text.cString);
}

@end
