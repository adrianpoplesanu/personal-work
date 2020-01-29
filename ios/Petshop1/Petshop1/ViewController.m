//
//  ViewController.m
//  Petshop1
//
//  Created by Adrian Poplesanu on 1/28/20.
//  Copyright © 2020 Adrian Poplesanu. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController {
    NSArray *sweet_dogs;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    sweet_dogs = [NSArray arrayWithObjects: @"Dexiciul", @"Lunitza", @"Sashic", nil];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger) tableView:(UITableView *) tableView numberOfRowsInSection:(NSInteger)section {
    return [sweet_dogs count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *simpleTableIdentifier = @"SimpleTableCell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:simpleTableIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier: simpleTableIdentifier];
    }
    
    cell.textLabel.text = [sweet_dogs objectAtIndex:indexPath.row];
    return cell;
}

@end
