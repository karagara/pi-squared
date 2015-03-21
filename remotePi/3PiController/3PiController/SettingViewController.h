//
//  MainConsoleController.m
//  3PiController
//
//  Created by Yan & Colten on 15/2/23.
//  Copyright (c) 2015 3piControllerIOS. All rights reserved.
//

#import <UIKit/UIKit.h> 
#import <Foundation/Foundation.h>
#import "ViewController.h"
#import "AppDelegates.h"

@interface SettingViewController: UIViewController <UINavigationControllerDelegate>{
    
}

@property(nonatomic, strong) IBOutlet UIButton *btSave;
@property(nonatomic, strong) IBOutlet UIButton *btClear;
@property(nonatomic, strong) IBOutlet UITextField *ip;
@property(nonatomic, strong) IBOutlet UITextField *port;
@property(nonatomic, strong) IBOutlet UISlider *slider;
@property(nonatomic, strong) IBOutlet UILabel *speed;

- (IBAction)View_TouchDown:(id)sender;
- (IBAction)doSave:(id)sender;
- (IBAction)doClear:(id)sender;
- (IBAction)changeSpeed:(UISlider *)sender;

@end