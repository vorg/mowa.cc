//
//  DirectMemoryAccessAppDelegate.m
//  DirectMemoryAccess
//
//  Created by Marcin Ignac on 12/22/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "DirectMemoryAccessAppDelegate.h"

@implementation DirectMemoryAccessAppDelegate

@synthesize window;


- (void)applicationDidFinishLaunching:(UIApplication *)application { 
	[[UIApplication sharedApplication] setStatusBarHidden:YES animated:NO];
    viewController = [[GLViewController alloc] init];
	[window addSubview:viewController.view];
    [window makeKeyAndVisible];
}


- (void)dealloc {
	[viewController release];
    [window release];
    [super dealloc];
}


@end
