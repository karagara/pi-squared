//
//  ViewController.m
//  3PiController
//
//  Created by Yu XI on 15/2/23.
//  Copyright (c) 2015年 3piControllerIOS. All rights reserved.
//

//using CFNetwork to connect to raspberry PI

#import "ViewController.h"
#import "SettingViewController.h"
#import "MainConsoleController.h"


@implementation ViewController

@synthesize inputS;
@synthesize hostName;
@synthesize portNumber;
@synthesize outputS = _outputS;


static ViewController *instance;

// Do any additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"3Pi Robot Controller";
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Main Page" style:UIBarButtonItemStylePlain target:nil action:nil];
    self.navigationItem.backBarButtonItem = backButton;
    [self.connStatus setText:@"Not Connected"];
}

- (void) viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    //load the ip address and port number which is saved by user
    
    if ([[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.ipAddress"] != nil) {
        hostName = [[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.ipAddress"];
       
        //NSLog(@"instance assigned");
    }
    if ([[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.portNumber"] != nil) {
        portNumber = [[NSUserDefaults standardUserDefaults] objectForKey:@"3pi.portNumber"];
    }
}

//release any cached data, release the view
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void) viewDidUnload{
    [super viewDidUnload];
}

- (IBAction)doSetting:(id)sender{
    SettingViewController *settingViewController = [[SettingViewController alloc] initWithNibName:@"SettingView" bundle:nil ];
    settingViewController.title = @"3Pi Robot Settings";
    [self.navigationController pushViewController:settingViewController animated:YES];
}

- (IBAction)doConnect:(id)sender {
    [self initializeNetworkComm];
    [self.connStatus setText:@"Connecting...."];
    NSString *response  = [NSString stringWithFormat:@"Testing connection"];
    NSData *data = [[NSData alloc] initWithData:[response dataUsingEncoding:NSASCIIStringEncoding]];
    [outputS write:[data bytes] maxLength:[data length]];
    NSLog(@"%@, %@", hostName, portNumber);
    
    while (([outputS streamStatus] != NSStreamStatusOpen && [outputS streamStatus] != NSStreamStatusError)) {
        [self.connStatus performSelectorOnMainThread:@selector(setText:) withObject:@"Connection in progress…" waitUntilDone:YES];
    }
    if ([outputS streamStatus] == NSStreamStatusOpen) {
        [self.connStatus performSelectorOnMainThread:@selector(setText:) withObject:[NSString stringWithFormat:@"Connected to %@:%@", hostName, portNumber] waitUntilDone:YES];
    } else if ([outputS streamStatus] == NSStreamStatusError) {
        [self.connStatus performSelectorOnMainThread:@selector(setText:) withObject:@"Could not connect to 3pi" waitUntilDone:YES];
    } else {
        [self.connStatus performSelectorOnMainThread:@selector(setText:) withObject:@"Not connected to 3pi" waitUntilDone:YES];
    }
}

- (IBAction)linktoMainConsole:(id)sender{
    MainConsoleController *mainConsoleController = [[MainConsoleController alloc] initWithNibName:@"mainConsole" bundle:nil];
    mainConsoleController.title = @"Robot & Rasp Pi Main Console";
    [self.navigationController pushViewController:mainConsoleController animated:YES];
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

+ (ViewController*)getInstance{
    instance = [[self alloc] init];
    return instance;
}

@end
