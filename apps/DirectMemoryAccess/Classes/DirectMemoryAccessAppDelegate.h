//
//  DirectMemoryAccessAppDelegate.h
//  DirectMemoryAccess
//
//  Created by Marcin Ignac on 12/22/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLViewController.h"


@interface DirectMemoryAccessAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
	GLViewController* viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@end

