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
    NSArray *sweet_dogs_image;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    sweet_dogs = [NSArray arrayWithObjects: @"Dexiciul", @"Lunitza", @"Sashic", @"Servetel", nil];
    sweet_dogs_image = [NSArray arrayWithObjects: @"dexiciul.jpg", @"lunitza.jpg", @"sashic.jpg", @"servetel.jpg", nil];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger) tableView:(UITableView *) tableView numberOfRowsInSection:(NSInteger)section {
    return [sweet_dogs count];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 100;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *simpleTableIdentifier = @"SimpleTableCell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:simpleTableIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier: simpleTableIdentifier];
    }
    
    cell.textLabel.text = [sweet_dogs objectAtIndex:indexPath.row];
    //cell.imageView.frame = CGRectMake(0, 0, 84, 84);
    cell.imageView.image = [UIImage imageNamed:[sweet_dogs_image objectAtIndex:indexPath.row]];
    return cell;
}

@end
