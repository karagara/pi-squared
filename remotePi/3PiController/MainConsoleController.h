//
//  MainConsoleController.h
//  3PiController
//
//  Created by Yu XI on 15/2/23.
//  Copyright (c) 2015年 3piControllerIOS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ViewController.h"
@interface MainConsoleController: UIViewController <NSStreamDelegate>{
    NSString *portNumber;
    NSOutputStream *outputS;
    NSInputStream *inputS;
    NSString *hostName;
}

@property(nonatomic, strong) IBOutlet UIButton *doUp;
@property(nonatomic, strong) IBOutlet UIButton *doDown;
@property(nonatomic, strong) IBOutlet UIButton *doLeft;
@property(nonatomic, strong) IBOutlet UIButton *doRight;
@property(nonatomic, strong) IBOutlet UIButton *doStop;
@property(nonatomic, strong) IBOutlet UIImageView *image;
@property(nonatomic, strong) NSInputStream *inputS;
@property(nonatomic, strong) NSOutputStream *outputS;
@property(nonatomic, strong) NSString *hostName;
@property(nonatomic, strong) NSString *portNumber;

-(IBAction)goUp:(id)sender;
-(IBAction)goDown:(id)sender;
-(IBAction)goLeft:(id)sender;
-(IBAction)goRight:(id)sender;
-(IBAction)stop:(id)sender;

@end