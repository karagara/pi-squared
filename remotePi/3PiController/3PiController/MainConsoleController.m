//
//  MainConsoleController.m
//  3PiController
//
//  Created by Yu XI on 15/2/23.
//  Copyright (c) 2015年 3piControllerIOS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MainConsoleController.h"

@implementation MainConsoleController

@synthesize inputS;
@synthesize portNumber;
@synthesize outputS;
@synthesize hostName;

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void) viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    //load the ip address and port number which is saved by user
    
    if ([[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.ipAddress"] != nil) {
        hostName = [[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.ipAddress"];
        
        NSLog(@"instance assigned");
    }
    if ([[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.portNumber"] != nil) {
        portNumber = [[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.portNumber"];
    }
}


-(IBAction)goUp:(id)sender{
    [self sendCommand:@"forward"];
    //NSLog(@"forward");
}

-(IBAction)goDown:(id)sender{
    [self sendCommand:@"back"];
    //NSLog(@"back");
}

-(IBAction)goLeft:(id)sender{
    [self sendCommand:@"left"];
    //NSLog(@"left");
}

-(IBAction)goRight:(id)sender{
    [self sendCommand:@"right"];
    //NSLog(@"right");
}

-(IBAction)stop:(id)sender{
    [self sendCommand:@"stop"];
    //NSLog(@"stop");
}

- (void) sendCommand: (NSString *) command{
    [self initializeNetworkComm];
    //ViewController *viewController = [ViewController getInstance];
    //NSOutputStream *outputS = [viewController getOutputStream];
    //NSString *host = viewController.hostName;
    NSData *data = [[NSData alloc] initWithData:[command dataUsingEncoding:NSASCIIStringEncoding]];
    [outputS write:[data bytes] maxLength:[data length]];
    //NSLog(@"%@", host);
}

- (void)initializeNetworkComm {
    CFReadStreamRef readS;
    CFWriteStreamRef writeS;
    CFStreamCreatePairWithSocketToHost(NULL, (CFStringRef) CFBridgingRetain(hostName), [portNumber intValue], &readS, &writeS);
    inputS = (__bridge NSInputStream *) readS;
    outputS = (__bridge NSOutputStream *) writeS;
    [inputS setDelegate:self];
    [outputS setDelegate:self];
    [inputS scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputS scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [inputS open];
    [outputS open];
}
@end

