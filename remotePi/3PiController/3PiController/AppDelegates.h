//
//  AppDelegate.h
//  3PiController
//
//  Created by Yu XI on 15/2/23.
//  Copyright (c) 2015年 3piControllerIOS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface AppDelegates : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    UINavigationController *navigationController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) UINavigationController *navigationController;


@end

