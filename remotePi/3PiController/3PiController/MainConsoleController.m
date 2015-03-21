//
//  MainConsoleController.m
//  3PiController
//
//  Created by Yan & Colten on 15/2/23.
//  Copyright (c) 2015 3piControllerIOS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MainConsoleController.h"
#import <CoreMotion/CMMotionManager.h>


@interface MainConsoleController(){
    float _avgX, _avgY, _avgZ;
}

@property (nonatomic, strong) CMMotionManager *motman;
@property (nonatomic, strong) NSTimer *timerMotion;
- (void)addAcceleration:(CMAcceleration)acc;

@end


@implementation MainConsoleController

static AppDelegates *appDelegate;
@synthesize imageView;
@synthesize motman;
@synthesize motionMode;

- (void)viewDidLoad {
    [super viewDidLoad];
    appDelegate = (AppDelegates *) [[UIApplication sharedApplication] delegate];
    [motionMode setOn:NO animated:YES];
    NSTimer *timer = [NSTimer timerWithTimeInterval:0.01 target:self selector:@selector(changeImage) userInfo:nil repeats:YES];
    [timer fire];
    [[NSRunLoop mainRunLoop] addTimer: timer forMode:NSDefaultRunLoopMode];
    
    NSTimer *timerMControl = [NSTimer timerWithTimeInterval:0.01 target:self selector:@selector(MotionControl) userInfo:nil repeats:YES];
    [timerMControl fire];
    [[NSRunLoop mainRunLoop] addTimer: timerMControl forMode:NSDefaultRunLoopMode];
    
//    the implementation of the motion
    self.motman= [CMMotionManager new];
    if((self.motman.accelerometerAvailable) && (self.motman.gyroAvailable) ){
        [self startMonitoringMotion];
    }
    else{
        NSLog(@"The motion is not started");
    }
}

-(void) changeImage{
    NSURL *url = [NSURL URLWithString:@"http://192.168.1.42:8080/api/stream"];
    NSData *data = [[NSData alloc] initWithContentsOfURL:url];
    UIImage *img1 = [[UIImage alloc] initWithData:data];
    self.imageView.image = img1;
}

-(IBAction)capture:(id)sender{
    UIImage *captureImg = [[UIImage alloc] initWithCGImage:[self imageCapture]];
    UIImageWriteToSavedPhotosAlbum(captureImg, nil, nil, nil);
}

-(CGImageRef)imageCapture{
    UIGraphicsBeginImageContext(self.imageView.bounds.size);
    [self.imageView.layer renderInContext:UIGraphicsGetCurrentContext()];
    UIImage *captureImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    CGRect rect = CGRectMake(0, 0, self.imageView.bounds.size.width, self.imageView.bounds.size.height);
    CGImageRef imageRef = CGImageCreateWithImageInRect([captureImage CGImage], rect);
    return imageRef;
}


-(void) MotionControl{
    bool switchStatus = motionMode.on;
    if( switchStatus ){
        if (_avgX < - 0.5 ){
            [self sendCommand:@"right"];
            NSLog(@"Send LEFT command");
        }
        else if (_avgX > 0.5 ){
            [self sendCommand:@"left"];
            NSLog(@"Send RIGHT command");
        }
        else if (_avgY > 0.5 ){
            [self sendCommand:@"forward"];
            NSLog(@"Send FORWARD command");
        }
        else if (_avgY < - 0.5 ){
            [self sendCommand:@"back"];
            NSLog(@"Send BACK command");
        }
        else{
            [self sendCommand:@"stop"];
            NSLog(@"Send STOP command");
        }
    }
}

#pragma mark - service methods
- (void)startMonitoringMotion
{
    self.motman.accelerometerUpdateInterval = 1.0/kMOTIONUPDATEINTERVAL;
    self.motman.gyroUpdateInterval = 1.0/kMOTIONUPDATEINTERVAL;
    self.motman.showsDeviceMovementDisplay = YES;
    [self.motman startAccelerometerUpdates];
    [self.motman startGyroUpdates];
    self.timerMotion = [NSTimer scheduledTimerWithTimeInterval:self.motman.accelerometerUpdateInterval
                                                  target:self selector:@selector(pollMotion:)
                                                userInfo:nil
                                                 repeats:YES];
}

- (void)stopMonitoringMotion
{
    [self.motman stopAccelerometerUpdates];
    [self.motman stopGyroUpdates];
}

-(void) pollMotion:(NSTimer *) timer{
    CMAcceleration acc = self.motman.accelerometerData.acceleration;
    CMRotationRate rot = self.motman.gyroData.rotationRate;
    float x, y, z;
    [self addAcceleration:acc];
    x = _avgX;
    y = _avgY;
    z = _avgZ;
}


#pragma mark - helpers
- (void)addAcceleration:(CMAcceleration)acc
{
    float alpha = 0.1;
    _avgX = alpha*acc.x + (1-alpha)*_avgX;
    _avgY = alpha*acc.y + (1-alpha)*_avgY;
    _avgZ = alpha*acc.z + (1-alpha)*_avgZ;
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
}


-(IBAction)goUp:(id)sender{
    [self sendCommand:@"forward"];
    NSLog(@"Send forward Command");
}

-(IBAction)goDown:(id)sender{
    [self sendCommand:@"back"];
    NSLog(@"Send back Command");
}

-(IBAction)goLeft:(id)sender{
    [self sendCommand:@"right"];
    NSLog(@"Send left Command");
}

-(IBAction)goRight:(id)sender{
    [self sendCommand:@"left"];
    NSLog(@"Send right Command");
}

-(IBAction)stop:(id)sender{
    [self sendCommand:@"stop"];
    NSLog(@"Send stop Command");
}

- (void) sendCommand: (NSString *) command{
    NSData *data = [[NSData alloc] initWithData:[command dataUsingEncoding:NSASCIIStringEncoding]];
    [appDelegate.outputStream write:[data bytes] maxLength:[data length]];
    
}
@end

