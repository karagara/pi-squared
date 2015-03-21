//
//  MainConsoleController.m
//  3PiController
//
//  Created by Yan & Colten on 15/2/23.
//  Copyright (c) 2015 3piControllerIOS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SettingViewController.h" 

@class ViewController;

@implementation SettingViewController
static AppDelegates *appDelegate;

- (void) viewDidLoad{
    [super viewDidLoad];
    appDelegate = (AppDelegates *) [[UIApplication sharedApplication] delegate];
    if ([[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.ipAddress"] != nil) {
        [self.ip setText:[[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.ipAddress"]];
    }
    if ([[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.portNumber"] != nil) {
        [self.port setText:[[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.portNumber"]];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

// Release any retained subviews of the main view.
- (void)viewDidUnload {
    [super viewDidUnload];
}


- (IBAction)View_TouchDown:(id)sender {
    //resignFirstResponder. hide the keyboard when touch down
    [[UIApplication sharedApplication] sendAction:@selector(resignFirstResponder) to:nil from:nil forEvent:nil];
}

-(IBAction)doSave:(id)sender {
    //save speed the user set
    NSString *s = self.speed.text;
    NSString *speedSet = [NSString stringWithFormat:@"speed%@",s];
    //if the receive side have the char starting at "s", so it will substring from the string and get the value of speed
    //and assign the speed to the 3pi-Robot
    [self sendCommand:speedSet];
    //save the user input host name and port number
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:[self.ip text] forKey:@"3pi.ipAddress"];
    [defaults setObject:[self.port text] forKey:@"3pi.portNumber"];
    [defaults synchronize];
}

-(IBAction)doClear:(id)sender {
    [self.ip setText:@" "];
    [self.port setText:@" "];
}

- (IBAction)changeSpeed:(UISlider *)sender{
    int val = sender.value;
    self.speed.text = [NSString stringWithFormat:@"%i",val];
}

- (void) sendCommand: (NSString *) command{
    NSData *data = [[NSData alloc] initWithData:[command dataUsingEncoding:NSASCIIStringEncoding]];
    [appDelegate.outputStream write:[data bytes] maxLength:[data length]];
}

@end

