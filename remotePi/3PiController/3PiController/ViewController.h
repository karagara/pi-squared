//  ViewController.h
//  3PiController
//
//  Created by Yan Liu on 15/2/23.
//  Copyright (c) 2015  3piControllerIOS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
//useful for the motion control robot
#import <CoreMotion/CoreMotion.h>

@interface ViewController : UIViewController <NSStreamDelegate> {
    NSOutputStream *outputS;
    NSInputStream *inputS;
    NSString *hostName;
    NSString *portNumber;
}

@property(nonatomic, strong) IBOutlet UIButton *buttonConnect;
@property(nonatomic, strong) IBOutlet UIButton *buttonMainConsole;
@property(nonatomic, strong) IBOutlet UIButton *buttonSetting;
@property(nonatomic, strong) IBOutlet UILabel *connStatus;
@property(nonatomic, strong) NSInputStream *inputS;
@property(nonatomic, strong) NSOutputStream *outputS;
@property(nonatomic, strong) NSString *hostName;
@property(nonatomic, strong) NSString *portNumber;

- (IBAction)doSetting:(id)sender;
- (IBAction)doConnect:(id)sender;
- (IBAction)linktoMainConsole:(id)sender;
//get the instance of the outputS
+ (ViewController*)getInstance;

@end

